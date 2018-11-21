#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/PassManager.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Support/raw_ostream.h>
#include <vector>
#include <fstream>
using namespace llvm;

int main() {
    static Module *TheModule = new Module("demo", getGlobalContext());
    // Most of the codes are added with Builder.CreateXXX(...)
    // You may need SetInsertPoint(...) to choose inserted block
    // Learn more in IR/IRBuilder.h
    static IRBuilder<> Builder(getGlobalContext());
    FunctionPassManager FPM(TheModule);
    // Promote allocas to registers (mem2reg).
    FPM.add(createPromoteMemoryToRegisterPass());
    // Add other optimizations if you like.
    FPM.doInitialization();


    // extern int Output;
    GlobalVariable *Output =
        new GlobalVariable(*TheModule, IntegerType::get(getGlobalContext(), 32),
                false, GlobalValue::ExternalLinkage, 0, "Output");


    // declare function "main"
    std::vector<Type*> func_main_args;
    FunctionType *func_main_type =
        FunctionType::get(IntegerType::get(getGlobalContext(), 32),
                func_main_args, false);
    Function *func_main =
        Function::Create(func_main_type, GlobalValue::ExternalLinkage, "main", TheModule);

    BasicBlock *EntryBB = BasicBlock::Create(TheModule->getContext(), "", func_main, 0);
    Builder.SetInsertPoint(EntryBB);


    // foo = 10;
    // API: APInt(unsigned numBits, uint64_t val, bool isSigned = false);
    ConstantInt *FooVal = ConstantInt::get(TheModule->getContext(), APInt(32, 10));
    AllocaInst *Foo =
        Builder.CreateAlloca(IntegerType::get(TheModule->getContext(), 32), 0, "foo");
    Builder.CreateStore(FooVal, Foo);


    // While (foo > 0) {
    //     print();
    //     Output = foo;
    //     foo = foo - 1;
    // }

    //     br cond
    // cond:
    //     if (condition == true)
    //         br loop
    //     else
    //         br after
    // loop:
    //     ...
    //     br cond
    // after:
    BasicBlock *CondBB = BasicBlock::Create(getGlobalContext(), "cond", func_main);
    BasicBlock *LoopBB = BasicBlock::Create(getGlobalContext(), "loop", func_main);
    BasicBlock *AfterBB = BasicBlock::Create(getGlobalContext(), "after", func_main);

    // Happens in EntryBB
    Builder.CreateBr(CondBB);

    // Generate code in CondBB
    Builder.SetInsertPoint(CondBB);
    // compute (foo > 0)
    Value *CmpLVal = Builder.CreateLoad(Foo, "foo");
    Value *CmpRVal = ConstantInt::get(getGlobalContext(), APInt(32, 0));
    Value *Cond = Builder.CreateICmpUGT(CmpLVal, CmpRVal, "tmpcmp");
    // if (foo > 0)
    //     br loop;
    // else
    //     br after;
    Builder.CreateCondBr(Cond, LoopBB, AfterBB);

    // Generate code in LoopBB
    Builder.SetInsertPoint(LoopBB);
    // Output = foo;
    Value *TempVal = Builder.CreateLoad(Foo, "foo");
    Builder.CreateStore(TempVal, Output);
    // print();
    std::vector<Type*> func_print_args;
    FunctionType *func_print_type =
        FunctionType::get(Type::getVoidTy(getGlobalContext()),
                func_print_args, true);
    Function *func_print = Function::Create(
            func_print_type, GlobalValue::ExternalLinkage, "print", TheModule);
    Builder.CreateCall(func_print);
    // foo = foo - 1;
    Value *LoadFooVal = Builder.CreateLoad(Foo, "foo");
    Value *OneVal = ConstantInt::get(getGlobalContext(), APInt(32, 1));
    Value *FooSubOneVal = Builder.CreateSub(LoadFooVal, OneVal);
    Builder.CreateStore(FooSubOneVal, Foo);
    // Jump back to check loop condition
    Builder.CreateBr(CondBB);

    // Generate code in AfterBB
    Builder.SetInsertPoint(AfterBB);


    // return 0;
    ConstantInt *RetVal = ConstantInt::get(getGlobalContext(), APInt(32, 0));
    Builder.CreateRet(RetVal);


    // Add optimization
    FPM.run(*func_main);


    // dump IR to stderr
    TheModule->dump();
    return 0;
}
