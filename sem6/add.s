        .intel_syntax noprefix
        .text                          # секция кода (R-X)
        .globl  add_two
        .type   add_two, @function
add_two:
        .cfi_startproc                 # для корректного backtrace
        mov     rax, rdi               # 1-й аргумент → RAX
        add     rax, rsi               # RAX += 2-й аргумент
        ret
        .cfi_endproc
        .size   add_two, .-add_two
