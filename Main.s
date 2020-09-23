section .data
    InfoMessage1 db "Compiling program ", 0

section .bss
    Compiling resb 128
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
    MOV RDI, [Compiling]
    MOV RSI, 0
    MOV RDX, 0644o
    SYSCALL ; open buffer

    CMP RAX, -2

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

    MOV RAX, FileData
    CALL PutString
    RET
 
_start:
    ; Testing command line arguments
    POP RAX
    
    ; By default the kernel puts the path onto the argument stack
    CMP RAX, 1
    JE EndSequence

GetFileArguments:
    MOV [ArgumentCount], RAX
 
    POP RAX ; Pop of the file path

    MOV RAX, InfoMessage1
    CALL PutString

    POP RAX ; First argument
    MOV [Compiling], RAX
    CALL PutString

    ; Arguments found, run rest of code
    CALL ReadFile

EndSequence:
    CALL Terminate ; call end