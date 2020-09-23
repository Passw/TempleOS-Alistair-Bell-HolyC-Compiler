section .data


    ;;;;;;;;;;;;
    ;
    ;   DATA TYPES
    ;   All numerical data types will be represented by their bytes size
    ;   The improvment to the C language is the removal of "int", "short" & "double"
    ;   This in similiar to the types in <stdint.h>
    ;   Chars are removed and a string buffer uses u8 as we use 8 bit not 7 bit signed ascii
    ;
    ;;;;;;;;;;;;

    ; 8 bit / byte data types
    GRAMMER_8_BIT_UNSIGNED DB "u8"
    GRAMMER_8_BIT_SIGNED DB "i8"

    ; 16 bit types
    GRAMMER_16_BIT_UNSIGNED DB "u16"
    GRAMMER_16_BIT_SIGNED DB "i16"

    ; 32 bit data types
    GRAMMER_32_BIT_UNSIGNED DB "u32"
    GRAMMER_32_BIT_SIGNED DB "i32"

    ; 64 bit data types
    GRAMMER_64_BIT_UNSIGNED DB "u64"
    GRAMMER_64_BIT_SIGNED DB "i64"
    
    ; Floats and doubles
    GRAMMER_32_FLOAT DB "f32"
    GRAMMER_64_FLOAT DB "f64" ; double in C
    
    GRAMMER_VOID DB "void"
    
    ;;;;;;;;;;;;
    ; 
    ;   GENERAL KEYWORDS
    ;
    ;;;;;;;;;;;;
    GRAMMER_KEYWORD_WHILE DB "while"
    GRAMMER_KEYWORD_CONTINUE DB "continue"
    
    GRAMMER_KEYWORD_FOR DB "for"
    
    GRAMMER_KEYWORD_IF DB "if"
    GRAMMER_KEYWORD_ELSE DB "else"

    GRAMMER_KEYWORD_SWITCH DB "switch"
    GRAMMER_KEYWORD_CASE DB "case"
    GRAMMER_KEYWORD_DEFAULT DB "default"
    