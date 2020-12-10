.include "Defs.s"

StrLen: /* const I8 *str */
    popq  %rax /* Popping to then push is a efficient use of clock cycles*/
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
    

Strcmp: /* const  I8 *str1, const I8 *str2 */
    ret
