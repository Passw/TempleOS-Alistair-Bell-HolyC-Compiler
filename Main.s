section .data
    Compiling db "Tests/Variable.IC", 0

section .bss
    FileData resb 10240

section .text
    global _start

Terminate: ; Terminates the program
    MOV RAX, 231
    MOV RDI, 0
    SYSCALL
    RET

ReadFile:
    MOV RAX, 2
    MOV RDI, Compiling
    MOV RSI, 0
    MOV RDX, 0644o
    SYSCALL ; open buffer

    ; Probally should handle errors but oh well
    PUSH RAX
    MOV RDI, RAX
    MOV RAX, 0 ; sys read
    MOV RSI, FileData
    MOV RDX, 2048 ; bytes to read

    ; Close file
    MOV RDI, 3
    POP RDI
    SYSCALL

    MOV RAX, 1
    MOV RDI, 1
    MOV RSI, FileData
    MOV RDX, 10240
    SYSCALL

    RET

_start:
    CALL ReadFile
    CALL Terminate ; call end
