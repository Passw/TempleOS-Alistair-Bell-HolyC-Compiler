#ifndef LEXER_H
#define LEXER_H

#include "Common.h"
#include "Stream.h"
#include "Tokens.h"

typedef struct 
{

} IC_LexerCreateInfo;

typedef struct
{
    I8                          *CurrentStream;
    U32                         Line;
    U32                         LineOffset;
} IC_CompilingFile;

typedef struct
{
    const I8                    *Input;
} IC_LexerLoadStreamInfo;

typedef struct
{
    IC_CompilingFile            *Files;
    U32                         FileCount;
} IC_Lexer;

/* 
    Lexer
*/

extern void IC_LexerCreate(IC_Lexer *lexer, IC_LexerCreateInfo *info);
extern void IC_LexerLoadStream(IC_Lexer *lexer, IC_LexerLoadStreamInfo *info);
extern void IC_LexerStepForward(IC_Lexer *lexer);
extern void IC_LexerDestroy(IC_Lexer *lexer);


#endif