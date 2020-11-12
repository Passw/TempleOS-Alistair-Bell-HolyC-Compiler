#include "Lexer.h"

#define HC_LEXER_TOKEN_STRING_LENGTH 255
#define HC_LEXER_TOKEN_ROUND_COUNT 255

inline U8 HC_LexerCheckTerminationCharacterOrWhitespace(const I8 currentChar)
{
    return currentChar == '\n' 
        || currentChar == ' ' 
        || currentChar == '(' 
        || currentChar == ')' 
        || currentChar == '}' 
        || currentChar == '{'
        || currentChar == '['
        || currentChar == ']'
        || currentChar == ';'
        || currentChar == '\''  /* single quote */
        || currentChar == '\"'; /* double quote */
}
inline U8 HC_LexerCheckTerminationCharacterNotWhitespace(const I8 currentChar)
{
    return HC_LexerCheckTerminationCharacterOrWhitespace(currentChar) && (currentChar != ' ' && currentChar != '\n');
}

static inline U8 HC_LexerAddToken(HC_Lexer *l, HC_Token *t, const I8 *src, const U64 count)
{
    HC_TokenHandleInfo h;
    memset(&h, 0, sizeof(HC_TokenHandleInfo));
    strncpy(h.Source, src, count);
    h.Lexer = l;
    HC_TokenCreate(t, &h);
    return HC_True;
}
static inline U8 HC_LexerHandleNewToken(HC_Lexer *l, U8 *strMode, U8 *commentMode, U64 *tokenCount, const I8 *src, const U64 count)
{
    HC_Token t;
    HC_LexerAddToken(l, &t, src, count);
    switch (t.Token)
    {
        case HC_LEXICAL_TOKENS_STARTING_COMMENT:
            *commentMode = HC_True;
            break;
        case HC_LEXICAL_TOKENS_ENDING_COMMENT:
            *commentMode = HC_False;
            break;
        case HC_LEXICAL_TOKENS_SINGLE_QUOTE:
            *strMode = 1 - (*strMode);
            break;
        case HC_LEXICAL_TOKENS_DOUBLE_QUOTE:
            *strMode = 1 - (*strMode);
            break;
        
        default:
        {
            if (*commentMode == HC_False)
            {
                l->CurrentFile->Tokens = realloc(l->CurrentFile->Tokens, sizeof(HC_Token) * (*tokenCount + 1));
                memcpy(&l->CurrentFile->Tokens[*tokenCount], &t, sizeof(HC_Token));
                *tokenCount += 1;
            }
        }
    }
    return HC_True;
}

U8 HC_LexerCreate(HC_Lexer *lexer, HC_LexerCreateInfo *info)
{
    assert(lexer != NULL);
    assert(info != NULL);
    memset(lexer, 0, sizeof(HC_Lexer));

    lexer->Files = calloc(info->LoadCount, sizeof(HC_CompilingFile));

    U64 i;
    for (i = 0; i < info->LoadCount; i++)
        HC_LexerLoadStream(lexer, &info->Loads[i]);
    return HC_True;
}
U8 HC_LexerLoadStream(HC_Lexer *lexer, HC_LexerLoadStreamInfo *info)
{
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
    file.Symbols        = calloc(0, sizeof(HC_LexerSymbol));
    file.SymbolCount    = 0;
    file.Tokens         = calloc(0, sizeof(HC_Token));
    file.TokenCount     = 0;
    file.FileName       = info->Input;
    memcpy(&lexer->Files[lexer->FileCount], &file, sizeof(HC_CompilingFile));
    
    lexer->FileCount++;
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
    
    U8 stringMode   = HC_False;
    U8 commentMode  = HC_False;

    HC_Token tokens[HC_LEXER_TOKEN_ROUND_COUNT]; /* all the tokens found */
    memset(tokens, 0, sizeof(HC_Token) * HC_LEXER_TOKEN_ROUND_COUNT); 
    
    I8 localBuffer[HC_LEXER_TOKEN_STRING_LENGTH]; /* local buffer for the raw token data */
    memset(localBuffer, 0, sizeof(I8) * HC_LEXER_TOKEN_STRING_LENGTH);

    I8 localBufferCopy[HC_LEXER_TOKEN_STRING_LENGTH];
    memset(localBufferCopy, 0, sizeof(I8) * HC_LEXER_TOKEN_STRING_LENGTH);

    strcpy(localSource, lexer->CurrentFile->CurrentStream);
    while (HC_True)
    {
        I8 currentChar = localSource[i];
        if (HC_LexerCheckTerminationCharacterOrWhitespace(currentChar))
        {
            rightPinscor = i;
            U64 diff = rightPinscor - leftPinscor;
            
            if (leftPinscor == rightPinscor || rightPinscor < leftPinscor || diff == 0)
                goto update;

            strncpy(localBuffer, localSource + leftPinscor, diff);
            HC_LexerStripToken(localBuffer);
            
            /* First char token */
            if (HC_LexerCheckTerminationCharacterNotWhitespace(localBuffer[0]))
            {
                HC_LexerHandleNewToken(lexer, &stringMode, &commentMode, &tokenCount, localBuffer, 1);
                /* Offset new buffer by one to ignore the last added*/
                strcpy(localBufferCopy, localBuffer);
                strncpy(localBuffer, localBufferCopy + 1, strlen(localBufferCopy));
            }

            /* Rest token */
            if (strlen(localBuffer) != 0)
                HC_LexerHandleNewToken(lexer, &stringMode, &commentMode, &tokenCount, localBuffer, diff);
            
            update:
                leftPinscor = rightPinscor;
        }
        
        if (i == strlen(localSource) + 1)
            break;
        
        i++;
        memset(localBuffer, 0, sizeof(localBuffer));
    }
    {
        /* Last token */
        U64 diff = strlen(localSource) - leftPinscor;
        strncpy(localBuffer, localSource + leftPinscor, diff);

        HC_LexerStripToken(localBuffer);
        if (strlen(localBuffer) != 0)
        {
            lexer->CurrentFile->Tokens = realloc(lexer->CurrentFile->Tokens, sizeof(HC_Token) * (tokenCount + 1));
            HC_LexerAddToken(lexer, &lexer->CurrentFile->Tokens[tokenCount], localBuffer, diff);
            
            tokenCount++;
        }
    }
    
    lexer->CurrentFile->TokenCount = tokenCount;
    return HC_True;
}

U8 HC_LexerDestroy(HC_Lexer *lexer)
{
    U32 i;
    for (i = 0; i < lexer->FileCount; i++)
    {
        free(lexer->Files[i].CurrentStream);
        free(lexer->Files[i].Symbols);
        free(lexer->Files[i].Tokens);
    }
    free(lexer->Files);

    return HC_True;
}
U8 HC_LexerStripToken(I8 *src)
{
    U32 i;
    U32 begin = 0;
    U32 end = strlen(src) - 1;

    while (isspace((U8) src[begin]))
        begin++;

    while ((end >= begin) && isspace((U8) src[end]))
        end--;

    // Shift all characters back to the start of the string array.
    for (i = begin; i <= end; i++)
        src[i - begin] = src[i];

    src[i - begin] = '\0'; // Null terminate string.
    return HC_True;
}