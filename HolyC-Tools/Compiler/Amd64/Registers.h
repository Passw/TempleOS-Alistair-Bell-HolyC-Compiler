#ifndef AMD64_REGISTERS_H
#define AMD64_REGISTERS_H

#include <Core-Backend/Common.h>

/* Amd64 instruction registers
    rax	  eax	 ax	    al	    Accumulator
    rbx	  ebx	 bx	    bl	    Base
    rcx	  ecx	 cx	    cl	    Counter
    rdx	  edx	 dx	    dl	    Data (commonly extends the A register)
    rsi	  esi	 si	    sil	    Source index for string operations
    rdi	  edi	 di	    dil	    Destination index for string operations
    rsp	  esp	 sp	    spl	    Stack Pointer
    rbp	  ebp	 bp	    bpl	    Base Pointer (meant for stack frames)
    r8	  r8d	 r8w	r8b	    General purpose
    r9	  r9d	 r9w	r9b	    General purpose
    r10	  r10d	 r10w	r10b	General purpose
    r11	  r11d	 r11w	r11b	General purpose
    r12	  r12d	 r12w	r12b	General purpose
    r13	  r13d	 r13w	r13b	General purpose
    r14	  r14d	 r14w	r14b	General purpose
    r15	  r15d	 r15w	r15b	General purpose
*/

/* 
    Special function registers
*/

#define HC_REGISTER_ACCUMULATOR_64_BITS_STRING              "rax"
#define HC_REGISTER_ACCUMULATOR_32_BITS_STRING              "eax"
#define HC_REGISTER_ACCUMULATOR_16_BITS_STRING              "ax"
#define HC_REGISTER_ACCUMULATOR_8_BITS_STRING               "al"

#define HC_REGISTER_BASE_64_BITS_STRING                     "rbx"
#define HC_REGISTER_BASE_32_BITS_STRING                     "ebx"
#define HC_REGISTER_BASE_16_BITS_STRING                     "bx"
#define HC_REGISTER_BASE_8_BITS_STRING                      "bl"

#define HC_REGISTER_COUNTER_64_BITS_STRING                  "rcx"
#define HC_REGISTER_COUNTER_32_BITS_STRING                  "ecx"
#define HC_REGISTER_COUNTER_16_BITS_STRING                  "cx"
#define HC_REGISTER_COUNTER_8_BITS_STRING                   "cl"

#define HC_REGISTER_DATA_64_BITS_STRING                     "rdx"
#define HC_REGISTER_DATA_32_BITS_STRING                     "edx"
#define HC_REGISTER_DATA_16_BITS_STRING                     "dx"
#define HC_REGISTER_DATA_8_BITS_STRING                      "dl"

#define HC_REGISTER_STRING_INDEX_64_BITS_STRING             "rsi"
#define HC_REGISTER_STRING_INDEX_32_BITS_STRING             "esi"
#define HC_REGISTER_STRING_INDEX_16_BITS_STRING             "si"
#define HC_REGISTER_STRING_INDEX_8_BITS_STRING              "sil"

#define HC_REGISTER_DESTINATION_INDEX_64_BITS_STRING        "rdi"
#define HC_REGISTER_DESTINATION_INDEX_32_BITS_STRING        "edi"
#define HC_REGISTER_DESTINATION_INDEX_16_BITS_STRING        "di"
#define HC_REGISTER_DESTINATION_INDEX_8_BITS_STRING         "dil"

#define HC_REGISTER_BASE_POINTER_64_BITS_STRING             "rbp"
#define HC_REGISTER_BASE_POINTER_32_BITS_STRING             "ebp"
#define HC_REGISTER_BASE_POINTER_16_BITS_STRING             "bp"
#define HC_REGISTER_BASE_POINTER_8_BITS_STRING              "bpl"

/* 
    General purpose registers
*/

#define HC_REGISTERS_GENERAL_PURPOSE_8_64_BITS_STRING       "r8"
#define HC_REGISTERS_GENERAL_PURPOSE_8_32_BITS_STRING       "r8d"
#define HC_REGISTERS_GENERAL_PURPOSE_8_16_BITS_STRING       "r8w"
#define HC_REGISTERS_GENERAL_PURPOSE_8_8_BITS_STRING        "r8b"

#define HC_REGISTERS_GENERAL_PURPOSE_9_64_BITS_STRING       "r9"
#define HC_REGISTERS_GENERAL_PURPOSE_9_32_BITS_STRING       "r9d"
#define HC_REGISTERS_GENERAL_PURPOSE_9_16_BITS_STRING       "r9w"
#define HC_REGISTERS_GENERAL_PURPOSE_9_8_BITS_STRING        "r9b"

#define HC_REGISTERS_GENERAL_PURPOSE_10_64_BITS_STRING      "r10"
#define HC_REGISTERS_GENERAL_PURPOSE_10_32_BITS_STRING      "r10d"
#define HC_REGISTERS_GENERAL_PURPOSE_10_16_BITS_STRING      "r10w"
#define HC_REGISTERS_GENERAL_PURPOSE_10_8_BITS_STRING       "r10b"

#define HC_REGISTERS_GENERAL_PURPOSE_11_64_BITS_STRING      "r11"
#define HC_REGISTERS_GENERAL_PURPOSE_11_32_BITS_STRING      "r11d"
#define HC_REGISTERS_GENERAL_PURPOSE_11_16_BITS_STRING      "r11w"
#define HC_REGISTERS_GENERAL_PURPOSE_11_8_BITS_STRING       "r11b"

#define HC_REGISTERS_GENERAL_PURPOSE_12_64_BITS_STRING      "r12"
#define HC_REGISTERS_GENERAL_PURPOSE_12_32_BITS_STRING      "r12d"
#define HC_REGISTERS_GENERAL_PURPOSE_12_16_BITS_STRING      "r12w"
#define HC_REGISTERS_GENERAL_PURPOSE_12_8_BITS_STRING       "r12b"

#define HC_REGISTERS_GENERAL_PURPOSE_13_64_BITS_STRING      "r13"
#define HC_REGISTERS_GENERAL_PURPOSE_13_32_BITS_STRING      "r13d"
#define HC_REGISTERS_GENERAL_PURPOSE_13_16_BITS_STRING      "r13w"
#define HC_REGISTERS_GENERAL_PURPOSE_13_8_BITS_STRING       "r13b"

#define HC_REGISTERS_GENERAL_PURPOSE_14_64_BITS_STRING      "r14"
#define HC_REGISTERS_GENERAL_PURPOSE_14_32_BITS_STRING      "r14d"
#define HC_REGISTERS_GENERAL_PURPOSE_14_16_BITS_STRING      "r14w"
#define HC_REGISTERS_GENERAL_PURPOSE_14_8_BITS_STRING       "r14b"

#define HC_REGISTERS_GENERAL_PURPOSE_15_64_BITS_STRING      "r15"
#define HC_REGISTERS_GENERAL_PURPOSE_15_32_BITS_STRING      "r15d"
#define HC_REGISTERS_GENERAL_PURPOSE_15_16_BITS_STRING      "r15w"
#define HC_REGISTERS_GENERAL_PURPOSE_15_8_BITS_STRING       "r15b"

#define HC_REGISTER_MAX_STRING_LENGTH 9

typedef struct HC_Register
{
    U64 MachineCode;
    I8  InstructionString[HC_REGISTER_MAX_STRING_LENGTH];
} HC_Register;

#endif