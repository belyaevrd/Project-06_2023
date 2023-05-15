section .text
global f1
global f2
global f3
global d

f1:
    push ebp
    mov ebp, esp
    mov ecx, 1
    finit
    fld qword[ebp+8]
    fldz
    fcomip
    jbe .Lf11
    fchs
    mov ecx, -1
.Lf11:
    fldl2e
    fmulp
    fld1
    fscale
    fxch ST1
    fld ST0
    frndint
    fcomi 
    jbe .Lf13
    fld1
    fsubp
.Lf13:
    fsubp 
    f2xm1
    fld1
    faddp
    fmulp 
    cmp ecx, 1
    je .Lf12 
    fld1
    fdivr
.Lf12:
    fld1
    fld1
    faddp
    faddp
    leave
    ret

df1:
    push ebp
    mov ebp, esp 
    mov ecx, 1
    finit
    fld qword[ebp+8]
    fldz
    fcomip
    jbe .Ldf11
    fchs
    mov ecx, -1
.Ldf11:
    fldl2e
    fmulp
    fld1
    fscale
    fxch ST1
    fld ST0
    frndint
    fcomi 
    jbe .Ldf13
    fld1
    fsubp
.Ldf13:
    fsubp 
    f2xm1
    fld1
    faddp
    fmulp 
    cmp ecx, 1
    je .Ldf12 
    fld1
    fdivr
.Ldf12:
    leave
    ret

f2:
    push ebp
    mov ebp, esp
    finit
    fld qword[ebp+8]
    sub esp, 4
    mov dword[esp], 2
    fild dword[esp]
    fmulp
    fchs
    mov dword[esp], 8
    fild dword[esp]
    faddp
    leave
    ret

df2:
    push ebp
    mov ebp, esp
    finit
    fld1
    fld1
    faddp
    fchs
    leave
    ret

f3:
    push ebp
    mov ebp, esp
    sub esp, 4
    mov dword[esp], -5
    finit
    fild dword[esp]
    fld qword[ebp+8]
    fdivp
    leave
    ret

df3:
    push ebp
    mov ebp, esp
    sub esp, 4
    mov dword[esp], 5
    finit
    fild dword[esp]
    fld qword[ebp+8]
    fld qword[ebp+8]
    fmulp
    fdivp
    leave
    ret

d:
    push ebp
    mov ebp, esp
    sub esp, 8
    mov eax, dword[ebp+12]
    mov [esp], eax
    mov eax, dword[ebp+16]
    mov [esp+4], eax

    mov eax, [ebp+8]
    cmp eax, f1
    jne .Ld1
    call df1
    jmp .Ld
.Ld1:
    cmp eax, f2
    jne .Ld2
    call df2
    jmp .Ld
.Ld2:
    call df3
.Ld:
    leave
    ret
