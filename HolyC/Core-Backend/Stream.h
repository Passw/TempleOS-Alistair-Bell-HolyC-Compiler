#ifndef STREAM_H
#define STREAM_H

#include "Common.h"

typedef struct HC_Stream
{
    U8              Reallocatable;
    U64             *StreamSize;
    I8              *Data;
    const I8        *Path;
} HC_Stream;

extern U8 HC_StreamCreate(HC_Stream *stream);


#endif