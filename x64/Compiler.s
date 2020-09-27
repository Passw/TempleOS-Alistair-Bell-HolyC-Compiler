section .data
    NoInputFiles DB "No input files specified", 10, 0
    InvalidFile DB "File not found : ", 0
    CompilingFile DB "Compiling file: ", 0
    
    NewLine DB "", 0, 10


section .bss
    Compiling resb 128
    FileData resb 10240
    ArgumentCount resb 8


section .text
    global _start

%include "x64/IO.s"

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

    CMP RAX, -2 ; -2 is for a invalid input
    JNE ReadBuffer

.label1:
    MOV RAX, InvalidFile
    CALL PutString

    MOV RAX, [Compiling]
    CALL PutString

    MOV RAX, NewLine
    CALL PutString
    JE EndSequence
    RET

ReadBuffer:
    PUSH RAX
    MOV RDI, RAX
    MOV RAX, 0 ; sys read
    MOV RSI, FileData
    MOV RDX, 2048 ; bytes to read

    ; Close file
    MOV RDI, 3
    POP RDI
    SYSCALL

    RET
    
_start:
    ; Testing command line arguments
    POP RAX
    
    ; By default the kernel puts the path onto the argument stack
    CMP RAX, 1
    JNE GetFileArguments

.label1:
    MOV RAX, NoInputFiles
    CALL PutString 
    CALL EndSequence
    RET

GetFileArguments:

    MOV [ArgumentCount], RAX
 
    POP RAX ; Pop of the file path

    POP RAX ; First argument
    MOV [Compiling], RAX

    MOV RAX, CompilingFile
    CALL PutString

    MOV RAX, [Compiling]
    CALL PutString

    MOV RAX, NewLine
    CALL PutString

    ; Arguments found, run rest of code
    CALL ReadFile

   
    CALL Terminate
    RET


EndSequence:
    CALL Terminate ; call end
