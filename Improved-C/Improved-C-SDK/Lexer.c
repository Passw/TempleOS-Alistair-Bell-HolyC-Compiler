#include "Lexer.h"

U8 IC_LexerCreate(IC_Lexer *lexer, IC_LexerCreateInfo *info)
{
    assert(lexer != NULL);
    assert(info != NULL);
    memset(lexer, 0, sizeof(IC_Lexer));

    lexer->Files = calloc(0, sizeof(IC_CompilingFile));

    return IC_True;
}
U8 IC_LexerLoadStream(IC_Lexer *lexer, IC_LexerLoadStreamInfo *info)
{
    U64 size;
    U8 *data = calloc(0, sizeof(U8));
  
    IC_Stream stream;
    memset(&stream, 0, sizeof(IC_Stream));
    stream.Path = info->Input;
    stream.Reallocatable = 1;
    stream.Data = data;
    stream.StreamSize = &size;
    U8 result = IC_StreamCreate(&stream);
    
    if (!result)
    {
        printf("Unable to create load stream\n");
        return IC_False;
    }

    lexer->Files        = calloc(lexer->FileCount + 1, sizeof(IC_CompilingFile));

    IC_CompilingFile file;
    memset(&file, 0, sizeof(IC_CompilingFile));
    file.CurrentStream  = data;
    file.Line           = 0;
    file.LineOffset     = 0;
    memcpy(&lexer->Files[lexer->FileCount], &file, sizeof(IC_CompilingFile));

    lexer->FileCount++;

    return IC_True;
}
U8 IC_LexerStepForward(IC_Lexer *lexer)
{
    return IC_True;
}
U8 IC_LexerDestroy(IC_Lexer *lexer)
{
    U32 i;
    for (i = 0; i < lexer->FileCount; i++)
        free(lexer->Files[i].CurrentStream);
    free(lexer->Files);

    return IC_True;
}