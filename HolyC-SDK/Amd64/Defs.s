/* Making all methods global */

/* 
    Functions:
        Assembly -> HolyC 
        All function params are pushed onto stack

        U0 foo(U64 i = 1, U64 j = 2, U64 k = 3)
        movq  %rax, $1 ; i
        pushq %rax
        
        movq  %rax, $2 ; j
        pushq %rax
        
        movq  %rax, $3 ; k
        pushq %rax

        Return methods are placed in the the accumulator
*/

.global PutChars


.global StrNew
.global StrLen
.global StrCpy
.global StrCmp
.global Str2I64
