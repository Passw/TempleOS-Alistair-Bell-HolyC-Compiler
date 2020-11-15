#ifndef AMD64_INSTRUCTIONS
#define AMD64_INSTRUCTIONS

#include <Core-Backend/Common.h>

/* 
    strung in front of opcodes
    pushq = push 64 bits to stack
*/

#define HC_INSTRUCTIONS_USE_8_BITS_STRING     "b"
#define HC_INSTRUCTIONS_USE_16_BITS_STRING    "w"
#define HC_INSTRUCTIONS_USE_32_BITS_STRING    "l"
#define HC_INSTRUCTIONS_USE_64_BITS_STRING    "q"
#define HC_INSTRUCTIONS_USE_80_BITS_STRING    "t"

/* Possibly remove 32 bit floats as HolyC only used F64 */
#define HC_INSTRUCTIONS_USE_32_BITS_FLOAT_STRING     "s"
#define HC_INSTRUCTIONS_USE_64_BITS_FLOAT_STRING     "l"


#endif