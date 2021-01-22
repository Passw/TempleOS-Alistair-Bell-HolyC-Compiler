#ifndef LEXER_H
#define LEXER_H

#include "Common.h"
#include "Stream.h"
#include "Tokens.h"

typedef enum
{
    HC_LEXER_FLAGS_NONE
} HC_LexerFlags;

typedef struct HC_CompilingFile
{
    const char                  *FileName;
    char                        *CurrentStream;
    HC_Token                    *Tokens;
    U64                         CharCount;
    U64                         TokenCount;         
} HC_CompilingFile;

typedef struct HC_LexerLoadStreamInfo
{
    const char                  *Input;
    HC_LexerFlags               LexerFlags;
} HC_LexerLoadStreamInfo;

typedef struct HC_LexerCreateInfo
{
    HC_LexerLoadStreamInfo  Loading;
} HC_LexerCreateInfo;

typedef struct HC_Lexer
{
    HC_CompilingFile            *File;
} HC_Lexer;

/* 
    Lexer
*/
extern U8 HC_LexerCheckTerminationCharacterOrWhitespace(const char currentChar, U32 *newLine);
extern U8 HC_LexerCheckTerminationCharacterNotWhitespace(const char currentChar, U32 *newLine);
extern U8 HC_LexerCreate(HC_Lexer *lexer, HC_LexerCreateInfo *info);
extern U8 HC_LexerStripToken(char *src);
extern U8 HC_LexerLoadStream(HC_Lexer *lexer, HC_LexerLoadStreamInfo *info);
extern U8 HC_LexerParse(HC_Lexer *lexer);
extern U8 HC_LexerDestroy(HC_Lexer *lexer);


#endif
