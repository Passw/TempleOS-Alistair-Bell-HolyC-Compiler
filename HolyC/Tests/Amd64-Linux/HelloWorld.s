.text
    .global _start

/* 
        b = byte (8 bit).
        s = single (32-bit floating point).
        w = word (16 bit).
        l = long (32 bit integer or 64-bit floating point).
        q = quad (64 bit).
        t = ten bytes (80-bit floating point).
*/


_start:
        
        movq   $len, %rdx
        movq   $msg, %rcx
        movq   $1, %rbx
        movq   $4, %rax
        int    $0x80

        movq    $0,%rbx
        movq    $1,%rax
        int     $0x80

.data

msg:
        .ascii  "Hello, world!\n"
        len = . - msg
