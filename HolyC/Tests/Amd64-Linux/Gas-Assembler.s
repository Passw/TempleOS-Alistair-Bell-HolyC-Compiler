.text
    .global _start

_start:
        
        mov    $len, %rdx
        mov    $msg, %rcx
        mov    $1, %rbx
        mov    $4, %rax
        int    $0x80

        mov     $0,%rbx
        mov     $1,%rax
        int     $0x80

.data

msg:
        .ascii  "Hello, world!\n"
        len = . - msg
