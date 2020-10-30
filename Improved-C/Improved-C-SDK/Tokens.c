#include "Tokens.h"
#include "Lexer.h"

#define IC_LEXICAL_TOKENS_SEMI_COLON_STRING_HASH    177632 /* ; */
#define IC_LEXICAL_TOKENS_PLUS_STRING_HASH          177616 /* + */
#define IC_LEXICAL_TOKENS_MINUS_STRING_HASH         177618 /* - */
#define IC_LEXICAL_TOKENS_MULTIPLY_STRING_HASH      177615 /* * */
#define IC_LEXICAL_TOKENS_DIVIDE_STRING_HASH        177620 /* / */
#define IC_LEXICAL_TOKENS_EQUALS_STRING_HASH        177634 /* = */  
#define IC_LEXICAL_TOKENS_FOR_STRING_HASH           193491852 /* for */
#define IC_LEXICAL_TOKENS_WHILE_STRING_HASH         210732529790 /* while */
#define IC_LEXICAL_TOKENS_I8_STRING_HASH            5862374   /* I8 */
#define IC_LEXICAL_TOKENS_U8_STRING_HASH            5862770   /* U8 */
#define IC_LEXICAL_TOKENS_I16_STRING_HASH           193458165 /* I16 */
#define IC_LEXICAL_TOKENS_U16_STRING_HASH           193471233 /* U16 */
#define IC_LEXICAL_TOKENS_I32_STRING_HASH           193458227 /* I32 */
#define IC_LEXICAL_TOKENS_U32_STRING_HASH           193471295 /* U32 */
#define IC_LEXICAL_TOKENS_I64_STRING_HASH           193458328 /* I64 */
#define IC_LEXICAL_TOKENS_U64_STRING_HASH           193471396 /* U64 */
#define IC_LEXICAL_TOKENS_F32_STRING_HASH           193454960 /* F32 */
#define IC_LEXICAL_TOKENS_F64_STRING_HASH           193455061 /* F64 */
#define IC_LEXICAL_TOKENS_VOID_STRING_HASH          6385805911 /* void */




#define IC_LEXICAL_TOKENS_MAX_STRING_HASH           18446744073709551615

/* Needs collison testing */
static U64 IC_TokenHashString(const I8 *source)
{
    unsigned long hash = 5381;
    int c;
    while (c = *source++)
        hash = ((hash << 5) + hash) + c;
    return hash;
}

U8 IC_TokenFromString(IC_Lexer *lexer, IC_Token *token, const I8 *source)
{
    assert(token != NULL);
    assert(lexer != NULL);

    token->ReferenceLine            = lexer->CurrentFile->Line;
    token->ReferenceLineIndex       = lexer->CurrentFile->LineOffset;
    
    switch (IC_TokenHashString(source))
    {
        case IC_LEXICAL_TOKENS_SEMI_COLON_STRING_HASH:
        {
            printf("[%s][operator]\n", source);
            token->Token = IC_LEXICAL_TOKENS_SEMI_COLON;
            break;
        }
        case IC_LEXICAL_TOKENS_PLUS_STRING_HASH:
        {
            printf("[%s][operator]\n", source);
            token->Token = IC_LEXICAL_TOKENS_PLUS;
            break;
        }
        case IC_LEXICAL_TOKENS_MINUS_STRING_HASH:
        {
            printf("[%s][operator]\n", source);
            token->Token = IC_LEXICAL_TOKENS_MINUS;
            break;
        }
        case IC_LEXICAL_TOKENS_MULTIPLY_STRING_HASH:
        {
            printf("[%s][operator]\n", source);
            token->Token = IC_LEXICAL_TOKENS_MULTIPLY;
            break;
        }
        case IC_LEXICAL_TOKENS_DIVIDE_STRING_HASH:
        {
            printf("[%s][operator]\n", source);
            token->Token = IC_LEXICAL_TOKENS_DIVIDE;
            break;
        }
        case IC_LEXICAL_TOKENS_EQUALS_STRING_HASH:
        {
            printf("[%s][assignment]\n", source);
            token->Token = IC_LEXICAL_TOKENS_EQUALS;
            break;
        }
        case IC_LEXICAL_TOKENS_FOR_STRING_HASH:
        {
            printf("[%s][keyword]\n", source);
            token->Token = IC_LEXICAL_TOKENS_FOR;
            break;
        }
        case IC_LEXICAL_TOKENS_WHILE_STRING_HASH:
        {
            printf("[%s][keyword]\n", source);
            token->Token = IC_LEXICAL_TOKENS_WHILE;
            break;
        }
        case IC_LEXICAL_TOKENS_I8_STRING_HASH:
        {
            printf("[%s][keyword]\n", source);
            token->Token = IC_LEXICAL_TOKENS_FOR;
            break;
        }
        case IC_LEXICAL_TOKENS_U8_STRING_HASH:
        {
            printf("[%s][keyword]\n", source);
            token->Token = IC_LEXICAL_TOKENS_U8;
            break;
        }
        case IC_LEXICAL_TOKENS_I16_STRING_HASH:
        {
            printf("[%s][keyword]\n", source);
            token->Token = IC_LEXICAL_TOKENS_I16;
            break;
        }
        case IC_LEXICAL_TOKENS_U16_STRING_HASH:
        {
            printf("[%s][keyword]\n", source);
            token->Token = IC_LEXICAL_TOKENS_U16;
            break;
        }
        case IC_LEXICAL_TOKENS_I32_STRING_HASH:
        {
            printf("[%s][keyword]\n", source);
            token->Token = IC_LEXICAL_TOKENS_I32;
            break;
        }
        case IC_LEXICAL_TOKENS_U32_STRING_HASH:
        {
            printf("[%s][keyword]\n", source);
            token->Token = IC_LEXICAL_TOKENS_U32;
            break;
        }
        case IC_LEXICAL_TOKENS_I64_STRING_HASH:
        {
            printf("[%s][keyword]\n", source);
            token->Token = IC_LEXICAL_TOKENS_I64;
            break;
        }
        case IC_LEXICAL_TOKENS_U64_STRING_HASH:
        {
            printf("[%s][keyword]\n", source);
            token->Token = IC_LEXICAL_TOKENS_U64;
            break;
        }
        case IC_LEXICAL_TOKENS_F32_STRING_HASH:
        {
            printf("[%s][keyword]\n", source);
            token->Token = IC_LEXICAL_TOKENS_F32;
            break;
        }
        case IC_LEXICAL_TOKENS_F64_STRING_HASH:
        {
            printf("[%s][keyword]\n", source);
            token->Token = IC_LEXICAL_TOKENS_F64;
            break;
        }
        case IC_LEXICAL_TOKENS_VOID_STRING_HASH:
        {
            printf("[%s][keyword]\n", source);
            token->Token = IC_LEXICAL_TOKENS_VOID;
            break;
        }
        default:
        {
            printf("[%s][identifier] - adding to symbol table\n", source);
            return IC_True;
        }
    }
    return IC_True;
}