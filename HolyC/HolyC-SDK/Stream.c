#include "Stream.h"

U8 HC_StreamCreate(HC_Stream *stream)
{
    assert(stream != NULL);
    assert(stream->Path != NULL);
    assert(stream->StreamSize != NULL);

    FILE *file = fopen(stream->Path, "r");

    if (file == NULL)
    {
        printf("Invalid file %s\n", stream->Path);
        return HC_True;
    }

    fseek(file, 0, SEEK_END);
    U64 size = ftell(file);
    
    if (stream->Reallocatable)
        stream->Data = realloc(stream->Data, size * sizeof(I8 *));

    fseek(file, 0, SEEK_SET);
    fread(stream->Data, 1, size, file);

    fclose(file);

    printf("Loading stream %s, length %lu\n", stream->Path, size);
    *stream->StreamSize = size;
    return HC_True;
}