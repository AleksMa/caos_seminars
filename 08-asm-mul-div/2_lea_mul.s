    .intel_syntax noprefix
    .global main
    .text
main:
    call    readi64
    mov     r12, rax
    lea rdi, [rax + 8 * rax]
    // rdi = (rax + 8 * rax + 1337)
    call    writei64
    call    finish
