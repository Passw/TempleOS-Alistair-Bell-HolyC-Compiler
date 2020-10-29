#include "Lexer.h"

void IC_LexerCreate(IC_Lexer *lexer, IC_LexerCreateInfo *info)
{
    assert(lexer != NULL);
    assert(info != NULL);
    memset(lexer, 0, sizeof(IC_Lexer));

    lexer->Files = calloc(0, sizeof(IC_CompilingFile));

}
void IC_LexerLoadStream(IC_Lexer *lexer, IC_LexerLoadStreamInfo *info)
{
    U64 size;
    U8 *data = calloc(0, sizeof(U8));
  
  
    IC_Stream stream;
    memset(&stream, 0, sizeof(IC_Stream));
    stream.Path = info->Input;
    stream.Reallocatable = 1;
    stream.Data = data;
    stream.StreamSize = &size;
    IC_StreamCreate(&stream);

    free(data);
}
void IC_LexerStepForward(IC_Lexer *lexer)
{

}
void IC_LexerDestroy(IC_Lexer *lexer)
{
    free(lexer->Files);
}