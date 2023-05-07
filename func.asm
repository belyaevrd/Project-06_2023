section .text
global f1
global f2
global f3
global d
;global df1
;global df2
;global df3

f1:
    push ebp
    mov ebp, esp
    mov eax, dword[ebp+8]
   
    mov ecx, 1
    fld qword[ebp+12]
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
    fstp qword[eax]
    leave
    ret

df1:
    push ebp
    mov ebp, esp
    mov eax, dword[ebp+8]
   
    mov ecx, 1
    fld qword[ebp+12]
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
    fstp qword[eax]
    leave
    ret

f2:
    push ebp
    mov ebp, esp
    mov eax, dword[ebp+8]
    fld qword[ebp+12]
    sub esp, 4
    mov dword[esp], 2
    fild dword[esp]
    fmulp
    fchs
    mov dword[esp], 8
    fild dword[esp]
    faddp
    fstp qword[eax]
    add esp, 4
    leave
    ret

df2:
    push ebp
    mov ebp, esp
    mov eax, dword[ebp+8]
    fld1
    fld1
    faddp
    fchs
    fstp qword[eax]
    leave
    ret

f3:
    push ebp
    mov ebp, esp
    mov eax, dword[ebp+8]
    sub esp, 4
    mov dword[esp], -5
    fild dword[esp]
    fld qword[ebp+12]
    fdivp
    fstp qword[eax]
    add esp, 4
    leave
    ret

df3:
    push ebp
    mov ebp, esp
    mov eax, dword[ebp+8]
    sub esp, 4
    mov dword[esp], 5
    fild dword[esp]
    fld qword[ebp+12]
    fld qword[ebp+12]
    fmulp
    fdivp
    fstp qword[eax]
    add esp, 4
    leave
    ret

d: ; d(double* x, void* f, double value)
    push ebp
    mov ebp, esp
    sub esp, 8
    mov eax, dword[ebp+16]
    mov [esp], eax
    mov eax, dword[ebp+20]
    mov [esp+4], eax
    push dword[ebp+8]

    mov eax, [ebp+12]
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
    add esp, 12
    leave
    ret
