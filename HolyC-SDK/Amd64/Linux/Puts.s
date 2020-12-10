PutCharsSet:
    movq  $1, %rax
    movq  $1, %rdi
    popq  %rdx /* len */
    popq  %rsi /* str */
    int   $0x80
    movq  $1, %rax /* success code */
    ret

PutChars:
    call  StrLen
    pushq %rax
    movq  %rax, 1
    movq  %rdi, 1
    popq  %rsi
    int   $0x80

    ret

