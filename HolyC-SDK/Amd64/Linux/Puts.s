PutChars:
    call  StrLen
    pushq %rax
    movq  %rax, 1
    movq  %rdi, 1
    popq  %rsi
    int   $0x80

    ret

