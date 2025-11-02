// ** Условие **
// Считать 2 числа, положить их на стек и вывести.

//  Содержимое стека      Адреса в памяти
//  -----------------     ---------------
//  (верх стека)          0x00010000  <-- (верхний конец/база стека, большой адрес)
//  |                     |
//  +-----------------+   0x0000FFFC
//  |   старые данные |   <-- элементы, ранее записанные (адреса уменьшаются)
//  +-----------------+   0x0000FFF8
//  |   старые данные |
//  +-----------------+   0x0000FFF4  <-- вершина стека (на неё указывает rsp)
//  |   текущие данные|   <-- сюда записали последний push
//  +-----------------+   0x0000FFF0
//  |   пустота       |
//  +-----------------+   0x0000FFEC
//  |       ...       |
//  +-----------------+   0x0000F048
//  |   пустота       |
//  +-----------------+   0x0000F044
//  |   пустота       |
//  +-----------------+   0x0000F040

    .intel_syntax noprefix
    .global main

main:
    mov r12, 0

cycle:
    mov rax, 1337
    push rax
    inc r12
    mov     rdi, r12
    call    writei64
    jmp cycle
    // [ return   xxxxx ]
    //   ^rsp
    // call    readi64
    // push    rax
    // // [ rax1, return   xxxxx ]
    //   ^rsp

    // call    readi64
    // push    rax
    // [ rax2, rax1, return   xxxxx ]
    //   ^rsp

    // Выведем то, что лежит под rsp (последнее введенное число)
    mov     rdi, rsp
    call    writei64
    // lea     rdi, [rip + var]
    // call    writei64
    // mov     rdi, [rsp + 8]
    // call    writei64


    // pop     rdi
    // call    writei64
    // [ rax1, return   xxxxx ]
    //   ^rsp

    // pop     rdi
    // call    writei64
    // [ return   xxxxx ]
    //   ^rsp

    // call    finish
// adjust size of stack ???

.data
var:
    .quad 0
