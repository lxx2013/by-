; ModuleID = 'demo'

@Output = external global i32

define i32 @main() {
  br label %cond

cond:                                             ; preds = %loop, %0
  %foo.0 = phi i32 [ 10, %0 ], [ %1, %loop ]
  %tmpcmp = icmp ugt i32 %foo.0, 0
  br i1 %tmpcmp, label %loop, label %after

loop:                                             ; preds = %cond
  store i32 %foo.0, i32* @Output
  call void (...)* @print()
  %1 = sub i32 %foo.0, 1
  br label %cond

after:                                            ; preds = %cond
  ret i32 0
}

declare void @print(...)
