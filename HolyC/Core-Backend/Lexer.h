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
    U64                         CharCount;
    HC_LexerSymbol              *Symbols;
    HC_Token                    *Tokens;
    U64                         TokenCount;         
    U64                         SymbolCount;
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
extern inline U8 HC_LexerCheckTerminationCharacterOrWhitespace(const I8 currentChar);
extern inline U8 HC_LexerCheckTerminationCharacterNotWhitespace(const I8 currentChar);
extern U8 HC_LexerCreate(HC_Lexer *lexer, HC_LexerCreateInfo *info);
extern U8 HC_LexerStripToken(I8 *src);
extern U8 HC_LexerLoadStream(HC_Lexer *lexer, HC_LexerLoadStreamInfo *info);
extern U8 HC_LexerParse(HC_Lexer *lexer);
extern U8 HC_LexerDestroy(HC_Lexer *lexer);


#endif