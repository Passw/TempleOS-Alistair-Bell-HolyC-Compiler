#include "Tokens.h"
#include "Lexer.h"

static inline U64 HC_TokenDetermineSpecialChar(HC_Token *token, HC_Token *previousToken)
{
    if (strlen(token->Source) != 1)
        return HC_False;

    switch (token->Hash)
    {
        case HC_LEXICAL_TOKENS_SEMI_COLON_STRING_HASH:
            token->Token = HC_LEXICAL_TOKEN_SEPARATOR;
            return HC_True;
        case HC_LEXICAL_TOKENS_PLUS_STRING_HASH:
            token->Token = HC_LEXICAL_TOKEN_OPERATOR;
            return HC_True;
        case HC_LEXICAL_TOKENS_MINUS_STRING_HASH:
            token->Token = HC_LEXICAL_TOKEN_OPERATOR;
            return HC_True;
        case HC_LEXICAL_TOKENS_MULTIPLY_STRING_HASH:
            token->Token = HC_LEXICAL_TOKEN_OPERATOR;
            return HC_True;
        case HC_LEXICAL_TOKENS_DIVIDE_STRING_HASH:
            token->Token = HC_LEXICAL_TOKEN_OPERATOR;
            return HC_True;
        case HC_LEXICAL_TOKENS_EQUALS_STRING_HASH:
            token->Token = HC_LEXICAL_TOKEN_OPERATOR;
            return HC_True;
        case HC_LEXICAL_TOKENS_LEFT_PARAM_STRING_HASH:
            token->Token = HC_LEXICAL_TOKEN_SCOPER;
            return HC_True;
        case HC_LEXICAL_TOKENS_RIGHT_PARAM_STRING_HASH:
            token->Token = HC_LEXICAL_TOKEN_SCOPER;
            return HC_True;
        case HC_LEXICAL_TOKENS_LEFT_CURLY_BRACKET_STRING_HASH:
            token->Token = HC_LEXICAL_TOKEN_SCOPER;
            return HC_True;
        case HC_LEXICAL_TOKENS_RIGHT_CURLY_BRACKET_STRING_HASH:
            token->Token = HC_LEXICAL_TOKEN_SCOPER;
            return HC_True;
        case HC_LEXICAL_TOKENS_SINGLE_QUOTE_STRING_HASH:
            token->Token = HC_LEXICAL_TOKEN_VALUE_PRECURSOR;
            return HC_True;
        case HC_LEXICAL_TOKENS_DOUBLE_QUOTE_STRING_HASH:
            token->Token = HC_LEXICAL_TOKEN_VALUE_PRECURSOR;
            return HC_True;
    }
    return HC_False;
}
static inline U8 HC_TokenDetermineType(HC_Token *token, HC_Token *previousToken)
{
    switch (token->Hash)
    {
        case HC_LEXICAL_TOKENS_STARTING_COMMENT_STRING_HASH:
            token->Token = HC_LEXICAL_TOKEN_UNRESOLVED;
            return HC_True;
        case HC_LEXICAL_TOKENS_ENDING_COMMENT_STRING_HASH:
            token->Token = HC_LEXICAL_TOKEN_UNRESOLVED;
            return HC_True;
        case HC_LEXICAL_TOKENS_FOR_STRING_HASH:
            token->Token = HC_LEXICAL_TOKEN_KEYWORD;
            return HC_True;
        case HC_LEXICAL_TOKENS_WHILE_STRING_HASH:
            token->Token = HC_LEXICAL_TOKEN_KEYWORD;
            return HC_True;
        case HC_LEXICAL_TOKENS_U0_STRING_HASH:
            token->Token = HC_LEXICAL_TOKEN_TYPES;
            return HC_True;
        case HC_LEXICAL_TOKENS_I8_STRING_HASH:
            token->Token = HC_LEXICAL_TOKEN_TYPES;
            return HC_True;
        case HC_LEXICAL_TOKENS_U8_STRING_HASH:
            token->Token = HC_LEXICAL_TOKEN_TYPES;
            return HC_True;
        case HC_LEXICAL_TOKENS_I16_STRING_HASH:
            token->Token = HC_LEXICAL_TOKEN_TYPES;
            return HC_True;
        case HC_LEXICAL_TOKENS_U16_STRING_HASH:
            token->Token = HC_LEXICAL_TOKEN_TYPES;
            return HC_True;
        case HC_LEXICAL_TOKENS_I32_STRING_HASH:
            token->Token = HC_LEXICAL_TOKEN_TYPES;
            return HC_True;
        case HC_LEXICAL_TOKENS_U32_STRING_HASH:
            token->Token = HC_LEXICAL_TOKEN_TYPES;
            return HC_True;
        case HC_LEXICAL_TOKENS_I64_STRING_HASH:
            token->Token = HC_LEXICAL_TOKEN_TYPES;
            return HC_True;
        case HC_LEXICAL_TOKENS_U64_STRING_HASH:
            token->Token = HC_LEXICAL_TOKEN_TYPES;
            return HC_True;
        case HC_LEXICAL_TOKENS_F32_STRING_HASH:
            token->Token = HC_LEXICAL_TOKEN_TYPES;
            return HC_True;
        case HC_LEXICAL_TOKENS_F64_STRING_HASH:
            token->Token = HC_LEXICAL_TOKEN_TYPES;
            return HC_True;
        default:
            token->Token = HC_LEXICAL_TOKEN_UNRESOLVED;
            return HC_True;
    }
    return HC_True;
}

/* Needs collision testing */
U64 HC_TokenHashString(const char *source)
{
    U64 hash = 5381;
    I32 c;
    while ((c = *source++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}
U64 HC_TokenHashChar(const char character)
{
    U64 hash = 5381;
    return ((hash << 5) + hash) + (I8)character;
}
U8 HC_TokenCreate(HC_Token *token, HC_TokenHandleInfo *info)
{
    assert(token != NULL);
    assert(info != NULL);
    memset(token, 0, sizeof(HC_Token));

    HC_LexerStripToken(info->Source);
    strcpy(token->Source, info->Source);

    token->Hash = HC_TokenHashString(token->Source);
    token->Line        = info->Line;
    
    if (info->SourceLength <= 1)
        HC_TokenDetermineSpecialChar(token, info->PreviousToken);
    else
        HC_TokenDetermineType(token, info->PreviousToken);        
    return HC_True;
}
