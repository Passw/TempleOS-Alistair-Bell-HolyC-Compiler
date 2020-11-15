#include "Stream.h"

#define HC_STREAM_MAX_FILE_BUFFER 1024 * 64 /* 64 mb */

U8 HC_StreamCreate(HC_Stream *stream)
{
    assert(stream != NULL);
    assert(stream->Path != NULL);
    assert(stream->StreamSize != NULL);

    FILE *file = fopen(stream->Path, "r");

    if (file == NULL)
    {
        printf("Invalid file %s\n", stream->Path);
        return HC_False;
    }

    fseek(file, 0, SEEK_END);
    U64 size = ftell(file);
    if (size >= HC_STREAM_MAX_FILE_BUFFER)
    {
        printf("Stream %s exceeds %luMb buffer limit (%luMb), failed to load\n", stream->Path, (U64)HC_STREAM_MAX_FILE_BUFFER / 1024, (U64)size / 1024);
        return HC_False;
    }
    
    if (stream->Reallocatable)
        stream->Data = realloc(stream->Data, size * sizeof(I8 *));

    fseek(file, 0, SEEK_SET);
    fread(stream->Data, 1, size, file);

    fclose(file);

    printf("Loading stream %s, length %lu\n", stream->Path, size);
    *stream->StreamSize = size;
    return HC_True;
}