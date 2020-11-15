#ifndef TYPES_H
#define TYPES_H

#include "Common.h"

/* 
    All values are in bytes
*/

typedef enum HC_DataTypeFlags
{
    HC_DATA_TYPE_FLAGS_SIGNED   = 0x1,
    HC_DATA_TYPE_FLAGS_UNSIGNED = 0x2,
    HC_DATA_TYPE_FLAGS_BUILT_IN = 0x4,
} HC_DataTypeFlags;

typedef struct HC_DataType
{
    const I8            *Name;
    HC_DataTypeFlags    Flags;
    U64                 Size;
} HC_DataType;


extern U8 HC_DataTypesGetDefault(HC_DataType *types, U64 *count, const U8 reallocatable);

#endif