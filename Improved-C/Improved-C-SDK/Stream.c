#include "Stream.h"

void IC_StreamCreate(IC_Stream *stream)
{
    assert(stream != NULL);
    assert(stream->Path != NULL);
    assert(stream->StreamSize != NULL);

    FILE *file = fopen(stream->Path, "r");
    assert(file != NULL);

    fseek(file, 0, SEEK_END);
    *stream->StreamSize = ftell(file);
    fclose(file);

    printf("Loading stream %s, length %lu\n", stream->Path, *stream->StreamSize);
}