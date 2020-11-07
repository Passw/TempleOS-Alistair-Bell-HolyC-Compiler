#include "Lexer.h"

#define HC_LEXER_TOKEN_STRING_LENGTH 255
#define HC_LEXER_TOKEN_ROUND_COUNT 255

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

    U64 i = 0; /* counter */
    U64 leftPinscor     = 0; /* start index for the new token string */
    U64 rightPinscor    = 0; /* end index for the new token string */
    I8 localSource[lexer->CurrentFile->CharCount]; /* local source to prevent stream modifications */
    U64 tokenCount = 0;
    
    HC_Token tokens[HC_LEXER_TOKEN_ROUND_COUNT]; /* all the tokens found */
    memset(tokens, 0, sizeof(HC_Token) * HC_LEXER_TOKEN_ROUND_COUNT); 
    
    I8 localBuffer[HC_LEXER_TOKEN_STRING_LENGTH]; /* local buffer for the raw token data */
    memset(localBuffer, 0, sizeof(I8) * HC_LEXER_TOKEN_STRING_LENGTH);

    strcpy(localSource, lexer->CurrentFile->CurrentStream);
    while (HC_True)
    {
        I8 currentChar = localSource[i];
        if (currentChar == '\n' || currentChar == '(' || currentChar == ')' || currentChar == '}' || currentChar == '{' || currentChar == ' ' || currentChar == ';')
        {
            rightPinscor = i;
             
            if (localSource[leftPinscor] == ' ' || leftPinscor == '\n' && (rightPinscor - leftPinscor != 1))
                leftPinscor++;

            U64 diff = rightPinscor - leftPinscor;
            
            if (leftPinscor == rightPinscor || rightPinscor < leftPinscor)
                goto update;

            lexer->CurrentFile->Tokens = realloc(lexer->CurrentFile->Tokens, sizeof(HC_Token) * (tokenCount + 1));
            memset(lexer->CurrentFile->Tokens[tokenCount].Source, 0, 255);
            
            strncpy(lexer->CurrentFile->Tokens[tokenCount].Source, localSource + leftPinscor, diff);
            tokenCount++;
        
            update:
                leftPinscor = rightPinscor;
                
        }

        if (i == strlen(localSource) + 1)
            break;
        
        endSequence:
        {
            i++;
            memset(localBuffer, 0, sizeof(localBuffer));
        }
    }
    finalChar:
    {
        lexer->CurrentFile->Tokens = realloc(lexer->CurrentFile->Tokens, sizeof(HC_Token) * (tokenCount + 1));
        strncpy(lexer->CurrentFile->Tokens[tokenCount].Source, localSource + leftPinscor, strlen(localSource) - leftPinscor);
        tokenCount++;
    }


    lexer->CurrentFile->TokenCount = tokenCount;
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