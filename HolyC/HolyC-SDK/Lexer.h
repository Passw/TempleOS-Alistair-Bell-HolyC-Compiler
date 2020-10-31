#ifndef LEXER_H
#define LEXER_H

#include "Common.h"
#include "Stream.h"
#include "Tokens.h"

typedef enum
{
    HC_LEXER_FLAGS_NONE
} HC_LexerFlags;

typedef struct HC_LexerCreateInfo
{

} HC_LexerCreateInfo;

typedef struct HC_LexerSymbol
{
    U64                         Hash;
    const I8                    *HashSource;
} HC_LexerSymbol;

typedef struct HC_CompilingFile
{
    I8                          *CurrentStream;
    U32                         Line;
    U32                         LineOffset;
    U64                         LineCount;
    HC_LexerSymbol              *Symbols;
    U32                         SymbolCount;
} HC_CompilingFile;

typedef struct HC_LexerLoadStreamInfo
{
    const I8                    *Input;
    HC_LexerFlags               LexerFlags;
} HC_LexerLoadStreamInfo;

typedef struct HC_Lexer
{
    HC_CompilingFile            *Files;
    HC_CompilingFile            *CurrentFile;
    U64                         FileCount;
} HC_Lexer;

/* 
    Lexer
*/

extern U8 HC_LexerCreate(HC_Lexer *lexer, HC_LexerCreateInfo *info);
extern U8 HC_LexerLoadStream(HC_Lexer *lexer, HC_LexerLoadStreamInfo *info);
extern U8 HC_LexerStepForward(HC_Lexer *lexer);
extern U8 HC_LexerSymbolAddTable(HC_Lexer *lexer, HC_LexerSymbol *symbol);
extern U8 HC_LexerDestroy(HC_Lexer *lexer);


#endif