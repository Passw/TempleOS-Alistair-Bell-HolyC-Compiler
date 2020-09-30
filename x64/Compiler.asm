section .data
    LogNoInputFiles DB "No input files specified", 0
    LogInvalidFile DB "File not found : ", 0
    LogCompilingFile DB "Compiling file: ", 0
    LogFileTooBig DB "Compiling file exceeds file buffer limit: ", 0
    NewLine DB "", 0, 10


section .bss
    Compiling RESB 128
    FileData RESB 10240
    StatData RESB 144
    ArgumentCount RESB 8

section .text
    global _start

%include "x64/IO.asm"

%define i8 byte
%define u8 byte

%define i16 word
%define u16 word

%define i32 dword
%define u32 dword

%define i64 qword 
%define u64 qword 


Terminate: ; Terminates the program
    MOV i64 RAX, NewLine
    CALL PutString

    MOV i64 RAX, 231
    MOV RDI, 0
    SYSCALL
    RET

OpenBufferStream:
    MOV i64 RAX, 2
    MOV RDI, [Compiling]
    MOV RSI, 0
    MOV RDX, 0644o
    SYSCALL ; open buffer

    CMP i64 RAX, -2 ; -2 is for a invalid input
    JNE GetBufferSize

.label1:
    MOV i64 RAX, NewLine
    CALL PutString

    MOV i64 RAX, LogInvalidFile
    CALL PutString

    MOV i64 RAX, [Compiling]
    CALL PutString
    
    CALL EndSequence
    RET

GetBufferSize:
    ; Finds the buffer size using stat 
    MOV i64 RAX, 4
    MOV RDI, [Compiling]
    MOV RSI, StatData
    SYSCALL

    ; File size in bytes has an offsetof 48 bytes and is a 64 bit integer
    MOV i64 RAX, [StatData + 48]
    CMP i64 RAX, 10240 ; Checking whether file file is greater than the buffer
    JB ReadBuffer

.label1:
    
    MOV i64 RAX, NewLine
    CALL PutString

    MOV i64 RAX, LogFileTooBig
    CALL PutString
    
    MOV i64 RAX, [Compiling]
    CALL PutString

    JMP EndSequence
    RET
        
ReadBuffer:
    PUSH QWORD RAX
    MOV RDI, RAX
    MOV i64 RAX, 0 ; sys read
    MOV RSI, FileData
    MOV RDX, 2048 ; bytes to read

    ; Close file
    MOV i64 RAX, 3
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
    MOV i64 RAX, LogNoInputFiles
    CALL PutString

    CALL EndSequence
    RET

GetFileArguments:

    MOV [ArgumentCount], RAX
 
    POP RAX ; Pop of the file path

    POP RAX ; First argument
    MOV [Compiling], RAX

    MOV i64 RAX, LogCompilingFile
    CALL PutString

    MOV i64 RAX, [Compiling]
    CALL PutString

    ; Arguments found, run rest of code
    CALL OpenBufferStream

Compilier:
    



    CALL EndSequence
    RET


EndSequence:
    CALL Terminate ; call end
