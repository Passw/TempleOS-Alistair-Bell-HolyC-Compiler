#include "Lexer.h"

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
    stream.StreamSize = &file.LineCount;
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
U8 HC_LexerStepForward(HC_Lexer *lexer)
{

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