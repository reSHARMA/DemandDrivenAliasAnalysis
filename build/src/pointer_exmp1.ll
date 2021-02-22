; ModuleID = 'pointer_exmp1.c'
source_filename = "pointer_exmp1.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@a = common global i32* null, align 8
@r = common global i32** null, align 8
@m = common global i32 0, align 4
@q = common global i32** null, align 8
@b = common global i32* null, align 8
@p = common global i32** null, align 8
@e = common global i32* null, align 8
@c = common global i32* null, align 8
@d = common global i32* null, align 8

; Function Attrs: noinline nounwind optnone uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  br label %2

; <label>:2:                                      ; preds = %9, %0
  store i32** @a, i32*** @r, align 8
  %3 = load i32**, i32*** @q, align 8
  store i32* @m, i32** %3, align 8
  %4 = load i32, i32* @m, align 4
  %5 = icmp ne i32 %4, 0
  br i1 %5, label %6, label %7

; <label>:6:                                      ; preds = %2
  store i32** @b, i32*** @q, align 8
  br label %8

; <label>:7:                                      ; preds = %2
  br label %10

; <label>:8:                                      ; preds = %6
  br label %9

; <label>:9:                                      ; preds = %8
  br i1 true, label %2, label %10

; <label>:10:                                     ; preds = %9, %7
  %11 = load i32**, i32*** @p, align 8
  %12 = load i32*, i32** %11, align 8
  store i32* %12, i32** @e, align 8
  store i32** @e, i32*** @q, align 8
  %13 = load i32, i32* %1, align 4
  ret i32 %13
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 6.0.0-1ubuntu2 (tags/RELEASE_600/final)"}
