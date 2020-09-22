section .data
    Compiling db "Tests/Variable.IC", 0
    Character db "Hello", 10, 0
    SingleCharacter db "H", 0

section .bss
    FileData resb 10240
    ArgumentCount resb 8

section .text
    global _start

%include "IO.s"

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
    MOV RDX, 1024

    MOV RAX, FileData
    CALL PutString

    RET
 
_start:
    ; Testing command line arguments
    POP RAX
    
    ; By default the kernel puts the path onto the argument stack
    CMP RAX, 1
    JE EndSequence

    ; Arguments found, run rest of code

    MOV RAX, Character
    CALL PutChar

    CALL ReadFile

EndSequence:

    CALL Terminate ; call end
    