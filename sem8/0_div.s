    .intel_syntax noprefix
    .global main
    .text
main:
    // xor rdx, rdx
    // mov rdx, 0xFFFFFFFFFFFFFFFF
    // mov rax, 0xFFFFFFFFFFFFFFFD
    mov rax, 15
    cqo
    mov rbx, 2
    // (rdx|rax) / rbx {+ rdx} –> rax
    idiv rbx
    mov rdi, rax
    push rdx
    call    writei64
    pop rdx
    mov rdi, rdx
    call    writei64
    call    finish
