#include "Stream.h"

U8 IC_StreamCreate(IC_Stream *stream)
{
    assert(stream != NULL);
    assert(stream->Path != NULL);
    assert(stream->StreamSize != NULL);

    FILE *file = fopen(stream->Path, "r");
    
    if (file == NULL)
    {
        printf("Invalid file %s\n");
        return IC_True;
    }

    fseek(file, 0, SEEK_END);
    *stream->StreamSize = ftell(file);
    fclose(file);

    printf("Loading stream %s, length %lu\n", stream->Path, *stream->StreamSize);
    return IC_True;
}