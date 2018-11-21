#!/bin/sh

# Generate IR
./bin/parser -d asgn.dot $1 $2

# Generate Obj
~/llvm3.6/build/bin/llc -filetype=obj asgn.dot.ll -o test.o

# Link
clang test.o bin/libdemo.a -o test.out

# run
./test.out