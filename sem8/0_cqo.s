    .intel_syntax noprefix
    .global main
    .text
main:
    call    readi64
    mov rdx, 1337
    cqo
    mov rdi, rdx
    call    writei64
    call    finish
