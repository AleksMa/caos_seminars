    // Простое использование переменной
    .intel_syntax noprefix
    .global main
.text
main:
    mov     qword ptr [rip + var], 500
    mov     rdi, [rip + var]
    call    writei64
    call    finish

.data
var:
    .quad    1337
    .quad    513        // [00000001][00000010]
    .quad    0

// .byte - 1 байт
// .word - 2 байта
// .int  - 4 байта
// .quad - 8 байт


// byte  ptr
// word  ptr
// dword ptr
// qword ptr

// [ base + index*scale + disp ]





// mov     qword ptr [var + rip], 500