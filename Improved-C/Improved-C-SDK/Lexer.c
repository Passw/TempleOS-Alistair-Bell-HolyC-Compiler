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
    lexer->Files        = calloc(lexer->FileCount + 1, sizeof(IC_CompilingFile));

    IC_CompilingFile file;
    memset(&file, 0, sizeof(IC_CompilingFile));
    file.CurrentStream = calloc(0, sizeof(I8 *));

    IC_Stream stream;
    memset(&stream, 0, sizeof(IC_Stream));
    stream.Path = info->Input;
    stream.Reallocatable = 1;
    stream.Data = file.CurrentStream;
    stream.StreamSize = &file.LineCount;
    U8 result = IC_StreamCreate(&stream);
    
    if (!result)
    {
        printf("Unable to load stream\n");
        return IC_False;
    }

    file.CurrentStream  = stream.Data;
    file.Line           = 0;
    file.LineOffset     = 0;
    file.Symbols        = calloc(0, sizeof(IC_LexerSymbol));
    file.SymbolCount    = 0;
    memcpy(&lexer->Files[lexer->FileCount], &file, sizeof(IC_CompilingFile));
    
    lexer->CurrentFile = &lexer->Files[lexer->FileCount];

    lexer->FileCount++;
    return IC_True;
}
U8 IC_LexerSymbolAddTable(IC_Lexer *lexer, IC_LexerSymbol *symbol)
{
    assert(lexer != NULL);
    assert(symbol != NULL);

    U32 symbolCount = lexer->CurrentFile->SymbolCount;
    lexer->CurrentFile->Symbols = realloc(lexer->CurrentFile->Symbols, (symbolCount + 1) * sizeof(IC_LexerSymbol));
    memcpy(&lexer->CurrentFile->Symbols[symbolCount], symbol, sizeof(IC_LexerSymbol));
    printf("Successfully added %s to symbol table\n", symbol->HashSource);
    lexer->CurrentFile->SymbolCount++;
 
    return IC_True;
}
U8 IC_LexerStepForward(IC_Lexer *lexer)
{

    return IC_False;
}
U8 IC_LexerDestroy(IC_Lexer *lexer)
{
    U32 i;
    for (i = 0; i < lexer->FileCount; i++)
    {
        free(lexer->Files[i].CurrentStream);
        free(lexer->Files[i].Symbols);
    }
    free(lexer->Files);

    return IC_True;
}