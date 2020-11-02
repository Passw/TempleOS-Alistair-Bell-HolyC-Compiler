#include "Lexer.h"

#define HC_LEXER_TOKEN_STRING_LENGTH 255
#define HC_LEXER_TOKEN_SUBSTRING_MAX_COUNT 25

U8 HC_LexerFindSubtokens(HC_Lexer *lexer, HC_Token *token, U64 *count, const I8 *source)
{
    I8 c;
    U8 foundSubtoken = HC_False;
    U64 i = 0;
    while (c = *source++)
    {
        HC_Token t;
        if (HC_TokenCheckSingleChar(lexer, &t, c))
        {
            memcpy(&token[i], &t, sizeof(HC_Token));
            i++;
            foundSubtoken = HC_True;
        }
    }
    *count = i;
    return foundSubtoken;
}

U8 HC_LexerCreate(HC_Lexer *lexer, HC_LexerCreateInfo *info)
{
    assert(lexer != NULL);
    assert(info != NULL);
    memset(lexer, 0, sizeof(HC_Lexer));

    lexer->Files = calloc(0, sizeof(HC_CompilingFile));

    return HC_True;
}
U8 HC_LexerLoadStream(HC_Lexer *lexer, HC_LexerLoadStreamInfo *info)
{
    lexer->Files        = calloc(lexer->FileCount + 1, sizeof(HC_CompilingFile));

    HC_CompilingFile file;
    memset(&file, 0, sizeof(HC_CompilingFile));
    file.CurrentStream = calloc(0, sizeof(I8 *));

    HC_Stream stream;
    memset(&stream, 0, sizeof(HC_Stream));
    stream.Path = info->Input;
    stream.Reallocatable = 1;
    stream.Data = file.CurrentStream;
    stream.StreamSize = &file.CharCount;
    U8 result = HC_StreamCreate(&stream);
    
    if (!result)
    {
        printf("Unable to load stream\n");
        return HC_False;
    }

    file.CurrentStream  = stream.Data;
    file.Line           = 0;
    file.LineOffset     = 0;
    file.Symbols        = calloc(0, sizeof(HC_LexerSymbol));
    file.SymbolCount    = 0;
    memcpy(&lexer->Files[lexer->FileCount], &file, sizeof(HC_CompilingFile));
    
    lexer->CurrentFile = &lexer->Files[lexer->FileCount];

    lexer->FileCount++;
    return HC_True;
}
U8 HC_LexerSymbolAddTable(HC_Lexer *lexer, HC_LexerSymbol *symbol)
{
    assert(lexer != NULL);
    assert(symbol != NULL);

    U32 symbolCount = lexer->CurrentFile->SymbolCount;
    lexer->CurrentFile->Symbols = realloc(lexer->CurrentFile->Symbols, (symbolCount + 1) * sizeof(HC_LexerSymbol));
    memcpy(&lexer->CurrentFile->Symbols[symbolCount], symbol, sizeof(HC_LexerSymbol));
    printf("Successfully added %s to symbol table\n", symbol->HashSource);
    lexer->CurrentFile->SymbolCount++;
 
    return HC_True;
}
U8 HC_LexerParse(HC_Lexer *lexer)
{
    assert(lexer != NULL);
    U64 newIndex = 0;
    U64 oldIndex = 0;
    U8 done = HC_False;

    U64 charCount = lexer->CurrentFile->CharCount;
    I8 localBuffer[HC_LEXER_TOKEN_STRING_LENGTH];
    I8 src[charCount];
    strcpy(src, lexer->CurrentFile->CurrentStream);

    while (HC_True)
    {
        if (src[newIndex] == ' ' || newIndex == (charCount - 1))
        {
            if (newIndex == (charCount - 1))
                goto finalCopy;
            memset(localBuffer, 0, sizeof(localBuffer));
            strncpy(localBuffer, src + oldIndex, newIndex - oldIndex);
            
            U64 count;
            HC_Token tokens[HC_LEXER_TOKEN_SUBSTRING_MAX_COUNT];
            printf("%s\n", localBuffer);
            HC_LexerFindSubtokens(lexer, tokens, &count, localBuffer);
            oldIndex = newIndex + 1;
        }
        newIndex++;
    }
    finalCopy:
    {
        strcpy(localBuffer, src + oldIndex);
        printf("%s\n", localBuffer);
    }

    
    end:
        return HC_True;
}
U8 HC_LexerDestroy(HC_Lexer *lexer)
{
    U32 i;
    for (i = 0; i < lexer->FileCount; i++)
    {
        free(lexer->Files[i].CurrentStream);
        free(lexer->Files[i].Symbols);
    }
    free(lexer->Files);

    return HC_True;
}
/*
inline U8 HC_LexerRemoveWhitespace(HC_Lexer *lexer, I8 *destination, const I8 *source)
{
    if (strlen(source) <= 1)
        return HC_True;
    const U64 sourceLen = strlen(source);
    U64 sourceIndex         = 0;
    U64 destinationIndex    = 0;

    while (source[sourceIndex] != '\0')
    {
        HC_Token token;
        I8 ca[1];
        ca[0] = source[sourceIndex];
        printf("%s\n", ca);
        HC_TokenCheckGrammer(lexer, &token, ca);
        
        sourceIndex++;
    }
    return HC_True;
}
*/

