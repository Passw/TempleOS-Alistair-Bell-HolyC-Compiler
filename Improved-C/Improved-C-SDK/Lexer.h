#ifndef LEXER_H
#define LEXER_H

#include "Common.h"
#include "Stream.h"
#include "Tokens.h"

typedef enum
{
    IC_LEXER_FLAGS_NONE
} IC_LexerFlags;

typedef struct IC_LexerCreateInfo
{

} IC_LexerCreateInfo;

typedef struct IC_LexerSymbol
{
    U64                         Hash;
    const I8                    *HashSource;
} IC_LexerSymbol;

typedef struct IC_CompilingFile
{
    I8                          *CurrentStream;
    U32                         Line;
    U32                         LineOffset;
    U64                         LineCount;
    IC_LexerSymbol              *Symbols;
    U32                         SymbolCount;
} IC_CompilingFile;

typedef struct IC_LexerLoadStreamInfo
{
    const I8                    *Input;
    IC_LexerFlags               LexerFlags;
} IC_LexerLoadStreamInfo;

typedef struct IC_Lexer
{
    IC_CompilingFile            *Files;
    IC_CompilingFile            *CurrentFile;
    U64                         FileCount;
} IC_Lexer;

/* 
    Lexer
*/

extern U8 IC_LexerCreate(IC_Lexer *lexer, IC_LexerCreateInfo *info);
extern U8 IC_LexerLoadStream(IC_Lexer *lexer, IC_LexerLoadStreamInfo *info);
extern U8 IC_LexerStepForward(IC_Lexer *lexer);
extern U8 IC_LexerSymbolAddTable(IC_Lexer *lexer, IC_LexerSymbol *symbol);
extern U8 IC_LexerDestroy(IC_Lexer *lexer);


#endif