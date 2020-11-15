#include "Types.h"

U8 HC_DataTypesGetDefault(HC_DataType *types, U64 *count, const U8 reallocatable)
{
    assert(types != NULL);
    assert(count != NULL);

    /* 
        Built in types

        U0  -  0 bit typeless  - 0B
        I8  -  8 bit signed    - 1B
        U8  -  8 bit unsigned  - 1B
        I16 -  16 bit signed   - 2B
        U16 -  16 bit unsigned - 2B
        I32 -  32 bit signed   - 4B
        U32 -  32 bit unsigned - 4B
        I64 -  16 bit signed   - 8B
        U64 -  16 bit unsigned - 8B
    */

    struct HC_DataType builtIn[9];
    memset(builtIn, 0, sizeof(builtIn));
    builtIn[0].Flags              = HC_DATA_TYPE_FLAGS_BUILT_IN;
    builtIn[0].Name               = "U0";
    builtIn[0].Size               = 0; /* void is ZERO size! */

    builtIn[1].Flags              = HC_DATA_TYPE_FLAGS_BUILT_IN | HC_DATA_TYPE_FLAGS_SIGNED;
    builtIn[1].Name               = "I8";
    builtIn[1].Size               = 1;

    builtIn[2].Flags              = HC_DATA_TYPE_FLAGS_BUILT_IN | HC_DATA_TYPE_FLAGS_UNSIGNED;
    builtIn[2].Name               = "U8";
    builtIn[2].Size               = 1;

    builtIn[3].Flags              = HC_DATA_TYPE_FLAGS_BUILT_IN | HC_DATA_TYPE_FLAGS_SIGNED;
    builtIn[3].Name               = "I16";
    builtIn[3].Size               = 2;

    builtIn[4].Flags              = HC_DATA_TYPE_FLAGS_BUILT_IN | HC_DATA_TYPE_FLAGS_UNSIGNED;
    builtIn[4].Name               = "U16";
    builtIn[4].Size               = 2;

    builtIn[5].Flags              = HC_DATA_TYPE_FLAGS_BUILT_IN | HC_DATA_TYPE_FLAGS_SIGNED;
    builtIn[5].Name               = "I32";
    builtIn[5].Size               = 4;

    builtIn[6].Flags              = HC_DATA_TYPE_FLAGS_BUILT_IN | HC_DATA_TYPE_FLAGS_UNSIGNED;
    builtIn[6].Name               = "U32";
    builtIn[6].Size               = 4;

    builtIn[7].Flags              = HC_DATA_TYPE_FLAGS_BUILT_IN | HC_DATA_TYPE_FLAGS_SIGNED;
    builtIn[7].Name               = "I64";
    builtIn[7].Size               = 8;

    builtIn[8].Flags              = HC_DATA_TYPE_FLAGS_BUILT_IN | HC_DATA_TYPE_FLAGS_UNSIGNED;
    builtIn[8].Name               = "U64";
    builtIn[8].Size               = 8;

    if (reallocatable)
        types = realloc(types, sizeof(types));
    memcpy(types, builtIn, sizeof(builtIn));

    *count = sizeof(builtIn) / sizeof(HC_DataType);

    return HC_True;
}