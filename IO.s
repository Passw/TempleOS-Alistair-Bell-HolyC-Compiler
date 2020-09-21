PutChar: ; Puts upto 8 bytes of character data
    MOV RAX, 1
    MOV RDI, 1
    MOV RDX, 8
    SYSCALL

