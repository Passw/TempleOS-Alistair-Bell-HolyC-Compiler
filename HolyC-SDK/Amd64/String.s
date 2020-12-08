.include "Defs.s"

StrLen:
    pushq %rax /* String data */
    movq  %rbx, 0

loop:
    incq  %rax
    incq  %rbx
    movb  %cl, (%rax)
    cmp   $0,  %cl /* string terminator */
    jne   loop
    popq  %rax
    movq  %rax, %rbx
    ret

Strcmp:
    


    ret
