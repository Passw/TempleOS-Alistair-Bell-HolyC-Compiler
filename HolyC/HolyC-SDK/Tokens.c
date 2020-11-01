#include "Tokens.h"
#include "Lexer.h"

#define HC_LEXICAL_TOKENS_SEMI_COLON_STRING_HASH    177632 /* ; */
#define HC_LEXICAL_TOKENS_PLUS_STRING_HASH          177616 /* + */
#define HC_LEXICAL_TOKENS_MINUS_STRING_HASH         177618 /* - */
#define HC_LEXICAL_TOKENS_MULTIPLY_STRING_HASH      177615 /* * */
#define HC_LEXICAL_TOKENS_DIVIDE_STRING_HASH        177620 /* / */
#define HC_LEXICAL_TOKENS_EQUALS_STRING_HASH        177634 /* = */  
#define HC_LEXICAL_TOKENS_LEFT_PARAM_STRING_HASH    177613 /* ( */
#define HC_LEXICAL_TOKENS_RIGHT_PARAM_STRING_HASH   177614 /* ) */
#define HC_LEXICAL_TOKENS_FOR_STRING_HASH           193491852 /* for */
#define HC_LEXICAL_TOKENS_WHILE_STRING_HASH         210732529790 /* while */
#define HC_LEXICAL_TOKENS_I8_STRING_HASH            5862374   /* I8 */
#define HC_LEXICAL_TOKENS_U8_STRING_HASH            5862770   /* U8 */
#define HC_LEXICAL_TOKENS_I16_STRING_HASH           193458165 /* I16 */
#define HC_LEXICAL_TOKENS_U16_STRING_HASH           193471233 /* U16 */
#define HC_LEXICAL_TOKENS_I32_STRING_HASH           193458227 /* I32 */
#define HC_LEXICAL_TOKENS_U32_STRING_HASH           193471295 /* U32 */
#define HC_LEXICAL_TOKENS_I64_STRING_HASH           193458328 /* I64 */
#define HC_LEXICAL_TOKENS_U64_STRING_HASH           193471396 /* U64 */
#define HC_LEXICAL_TOKENS_F32_STRING_HASH           193454960 /* F32 */
#define HC_LEXICAL_TOKENS_F64_STRING_HASH           193455061 /* F64 */
#define HC_LEXICAL_TOKENS_U0_STRING_HASH            5862762   /* U0 */




#define HC_LEXICAL_TOKENS_MAX_STRING_HASH           18446744073709551615

/* Needs collision testing */
static U64 HC_TokenHashString(const I8 *source)
{
    unsigned long hash = 5381;
    int c;
    while (c = *source++)
        hash = ((hash << 5) + hash) + c;
    return hash;
}

U8 HC_TokenCheckGrammer(HC_Lexer *lexer, HC_Token *token, const I8 *source)
{
    assert(token != NULL);
    assert(lexer != NULL);

    token->ReferenceLine            = lexer->CurrentFile->Line;
    token->ReferenceLineIndex       = lexer->CurrentFile->LineOffset;

    U64 hash = HC_TokenHashString(source);
    switch (hash)
    {
        case HC_LEXICAL_TOKENS_SEMI_COLON_STRING_HASH:
        {
            printf("[%s][operator]\n", source);
            token->Token = HC_LEXICAL_TOKENS_SEMI_COLON;
            return HC_True;
        }
        case HC_LEXICAL_TOKENS_PLUS_STRING_HASH:
        {
            printf("[%s][operator]\n", source);
            token->Token = HC_LEXICAL_TOKENS_PLUS;
            return HC_True;
        }
        case HC_LEXICAL_TOKENS_MINUS_STRING_HASH:
        {
            printf("[%s][operator]\n", source);
            token->Token = HC_LEXICAL_TOKENS_MINUS;
            return HC_True;
        }
        case HC_LEXICAL_TOKENS_MULTIPLY_STRING_HASH:
        {
            printf("[%s][operator]\n", source);
            token->Token = HC_LEXICAL_TOKENS_MULTIPLY;
            return HC_True;
        }
        case HC_LEXICAL_TOKENS_DIVIDE_STRING_HASH:
        {
            printf("[%s][operator]\n", source);
            token->Token = HC_LEXICAL_TOKENS_DIVIDE;
            return HC_True;
        }
        case HC_LEXICAL_TOKENS_EQUALS_STRING_HASH:
        {
            printf("[%s][assignment]\n", source);
            token->Token = HC_LEXICAL_TOKENS_EQUALS;
            return HC_True;
        }
        case HC_LEXICAL_TOKENS_LEFT_PARAM_STRING_HASH:
        {
            printf("[%s][scoper]\n", source);
            token->Token = HC_LEXICAL_TOKENS_LEFT_PARAM;
            return HC_True;
        }
        case HC_LEXICAL_TOKENS_RIGHT_PARAM_STRING_HASH:
        {
            printf("[%s][scoper]\n", source);
            token->Token = HC_LEXICAL_TOKENS_RIGHT_PARAM;
            return HC_True;
        }
        case HC_LEXICAL_TOKENS_FOR_STRING_HASH:
        {
            printf("[%s][keyword]\n", source);
            token->Token = HC_LEXICAL_TOKENS_FOR;
            return HC_True;
        }
        case HC_LEXICAL_TOKENS_WHILE_STRING_HASH:
        {
            printf("[%s][keyword]\n", source);
            token->Token = HC_LEXICAL_TOKENS_WHILE;
            return HC_True;
        }
        case HC_LEXICAL_TOKENS_I8_STRING_HASH:
        {
            printf("[%s][keyword]\n", source);
            token->Token = HC_LEXICAL_TOKENS_FOR;
            return HC_True;
        }
        case HC_LEXICAL_TOKENS_U8_STRING_HASH:
        {
            printf("[%s][keyword]\n", source);
            token->Token = HC_LEXICAL_TOKENS_U8;
            return HC_True;
        }
        case HC_LEXICAL_TOKENS_I16_STRING_HASH:
        {
            printf("[%s][keyword]\n", source);
            token->Token = HC_LEXICAL_TOKENS_I16;
            return HC_True;
        }
        case HC_LEXICAL_TOKENS_U16_STRING_HASH:
        {
            printf("[%s][keyword]\n", source);
            token->Token = HC_LEXICAL_TOKENS_U16;
            return HC_True;
        }
        case HC_LEXICAL_TOKENS_I32_STRING_HASH:
        {
            printf("[%s][keyword]\n", source);
            token->Token = HC_LEXICAL_TOKENS_I32;
            return HC_True;
        }
        case HC_LEXICAL_TOKENS_U32_STRING_HASH:
        {
            printf("[%s][keyword]\n", source);
            token->Token = HC_LEXICAL_TOKENS_U32;
            return HC_True;
        }
        case HC_LEXICAL_TOKENS_I64_STRING_HASH:
        {
            printf("[%s][keyword]\n", source);
            token->Token = HC_LEXICAL_TOKENS_I64;
            return HC_True;
        }
        case HC_LEXICAL_TOKENS_U64_STRING_HASH:
        {
            printf("[%s][keyword]\n", source);
            token->Token = HC_LEXICAL_TOKENS_U64;
            return HC_True;
        }
        case HC_LEXICAL_TOKENS_F32_STRING_HASH:
        {
            printf("[%s][keyword]\n", source);
            token->Token = HC_LEXICAL_TOKENS_F32;
            return HC_True;
        }
        case HC_LEXICAL_TOKENS_F64_STRING_HASH:
        {
            printf("[%s][keyword]\n", source);
            token->Token = HC_LEXICAL_TOKENS_F64;
            return HC_True;
        }
        case HC_LEXICAL_TOKENS_U0_STRING_HASH:
        {
            printf("[%s][keyword]\n", source);
            token->Token = HC_LEXICAL_TOKENS_U0;
            return HC_True;
        }
        default:
        {
            printf("[%s][undefined]\n", source);
            return HC_True;
        }
    }
}
U8 HC_TokenFromString(HC_Lexer *lexer, HC_Token *token, const I8 *source)
{
    assert(token != NULL);
    assert(lexer != NULL);

    U64 hash = HC_TokenHashString(source);
    if (HC_TokenCheckGrammer(lexer, token, source) == HC_False)
    {
        printf("[%s][identifier] - adding to symbol table\n", source);
        HC_LexerSymbol s;
        memset(&s, 0, sizeof(HC_LexerSymbol));
        s.Hash = hash;
        s.HashSource = source;
        HC_LexerSymbolAddTable(lexer, &s);
    }

    return HC_True;
}