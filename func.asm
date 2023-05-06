section .text
global f1
;global f2
;global f3
;global df1
;global df2
;global df3
f1:
    push ebp
    mov ebp, esp
; x <> 0
    fld0 ; pop st[0] or st[1] ?
    fld qword[ebp+8]
    fcomip
    jae .Lf1
    fchs
.Lf1:
    fldl2e
    fmulp
    f2xm1
    fld1
    fadd
    
    jae .Lf2
    fld1
    fdivr
.Lf2:
    fstp qword[ebp+12]
    leave
    ret
