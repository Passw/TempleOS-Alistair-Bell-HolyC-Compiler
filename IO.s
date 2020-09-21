PutChar: ; Puts upto 8 bytes of character data
    MOV RAX, 1
    MOV RDI, 1
    MOV RDX, 8
    SYSCALL
    RET

PutString:
    PUSH RAX
    MOV RBX, 0 ; string length

StringLoop:
    INC RAX
    INC RBX
    MOV CL, [RAX] ; We use 8 bit ascii not uncode unless the kernel requires
    CMP CL, 0 ; Check string termination
    JNE StringLoop

    ; If their is no terminator then the program will forever loop

    ; Call print
    MOV RAX, 1
    MOV RDI, 1
    POP RSI
    MOV RDX, RBX
    SYSCALL

    RET