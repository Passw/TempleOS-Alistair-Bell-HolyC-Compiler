#include "Lexer.h"

#define HC_LEXER_TOKEN_STRING_LENGTH 255

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
    I8 src[charCount];
    strcpy(src, lexer->CurrentFile->CurrentStream);

    while (!done)
    {
        I8 localBuffer[HC_LEXER_TOKEN_STRING_LENGTH];
        /* Second last char */
        if (newIndex == (charCount - 1))
        {
            strncpy(localBuffer, src + oldIndex, charCount - oldIndex);
            printf("%s\n", localBuffer);
            done = HC_True;
        }

        //printf("%c\n", src[newIndex]);
        if (src[newIndex] == ' ')
        {
            memset(localBuffer, 0, sizeof(localBuffer));
            strncpy(localBuffer, src + oldIndex, newIndex - oldIndex);
            printf("%s\n", localBuffer);
            oldIndex = newIndex + 1;
        }
        newIndex++;
    }

    return HC_False;
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
