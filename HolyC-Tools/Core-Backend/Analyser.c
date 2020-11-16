#include "Analyser.h"

typedef struct HC_SyntaxAnalyserExpressionCreateInfo
{
    U64 Offset;
    U64 Count;
} HC_SyntaxAnalyserExpressionCreateInfo;

static U0 HC_SyntaxAnalyserPrintTokens(HC_SyntaxAnalyser *analyser)
{
    U64 i;
    for (i = 0; i < analyser->AnalysingCount; i++)
        printf("[%3lu][%s]\n", i, analyser->Analysing[i].Source);
}
static U8 HC_SyntaxAnalyserCheckBuiltInType(const U64 hash)
{
    switch (hash)
    {
        case HC_LEXICAL_TOKENS_U0_STRING_HASH: return HC_True;
        case HC_LEXICAL_TOKENS_I8_STRING_HASH: return HC_True;
        case HC_LEXICAL_TOKENS_U8_STRING_HASH: return HC_True;
        case HC_LEXICAL_TOKENS_I16_STRING_HASH: return HC_True;
        case HC_LEXICAL_TOKENS_U16_STRING_HASH: return HC_True;
        case HC_LEXICAL_TOKENS_I32_STRING_HASH: return HC_True;
        case HC_LEXICAL_TOKENS_U32_STRING_HASH: return HC_True;
        case HC_LEXICAL_TOKENS_I64_STRING_HASH: return HC_True;
        case HC_LEXICAL_TOKENS_U64_STRING_HASH: return HC_True;
        case HC_LEXICAL_TOKENS_F32_STRING_HASH: return HC_True;
        case HC_LEXICAL_TOKENS_F64_STRING_HASH: return HC_True;
    }
    return HC_False;
}

static U8 HC_SyntaxAnalyserCreateExpressions(HC_SyntaxAnalyser *analyser, HC_SyntaxAnalyserExpressionCreateInfo *info)
{
    HC_Token *indexer = &analyser->Analysing[info->Offset + 0];
    
    /* Check built in type */
    if (HC_SyntaxAnalyserCheckBuiltInType(indexer->Hash))
    {
        if (info->Count == 1)
        {
            printf("Invalid syntax [line %d: index %d]: Expected expression after %s\n", indexer->Line, indexer->LineOffset + 1, indexer->Source);
            return HC_False;
        }
        
        indexer++;
        
        /* Check repetition */
        if (HC_SyntaxAnalyserCheckBuiltInType(indexer->Hash))
        {
            printf("Invalid syntax [line %d: index %d]: Repetition of type %s\n", indexer->Line, indexer->LineOffset + 1, indexer->Source);
            return HC_False;
        }
        else
        {
            printf("New symbol of %s with type %s\n", indexer->Source, analyser->Analysing[info->Offset].Source);
            /* Add to symbol table and validate no others in outwards scopes */
        }

    }
    /* Not built in type (referencing old symbol) */
    else
    {

    }
    
    return HC_True;
}

U8 HC_SyntaxAnalyserCreate(HC_SyntaxAnalyser *analyser, HC_SyntaxAnalyserCreateInfo *createInfo)
{
    assert(analyser != NULL);
    assert(createInfo != NULL);

    memset(analyser, 0, sizeof(HC_SyntaxAnalyser));
    HC_Lexer *l = createInfo->Lexer;

    analyser->StreamName = l->CurrentFile->FileName;
    analyser->Errors = calloc(0, sizeof(HC_Error));
    analyser->ErrorCount = 0;
    analyser->AnalysingCount = l->CurrentFile->TokenCount;

    U64 tc = l->CurrentFile->TokenCount;

    analyser->Analysing = calloc(l->CurrentFile->TokenCount, sizeof(HC_Token));
    memcpy(analyser->Analysing, l->CurrentFile->Tokens, tc * sizeof(HC_Token));
    return HC_True;
}
U8 HC_SyntaxAnalyserAnalyse(HC_SyntaxAnalyser *analyser)
{
    assert(analyser != NULL);
    printf("Analysing %s\n", analyser->StreamName);
    
    if (analyser->AnalysingCount <= 1)
    {
        printf("Expected expression!: Lack of tokens recognised \n");
        return HC_False;
    }
    
    U64 i         = 0;
    U64 leftPnsr  = 0;
    U64 rightPnsr = 0;
    U64 scope     = 0;

    HC_SyntaxAnalyserPrintTokens(analyser);

    while (HC_True)
    {
        rightPnsr = i;
        HC_Token *current = &analyser->Analysing[i];
        switch (current->Token)
        {
            case HC_LEXICAL_TOKENS_SEMI_COLON:
            {
                HC_SyntaxAnalyserExpressionCreateInfo ci;
                ci.Count  = (rightPnsr - leftPnsr);
                ci.Offset = leftPnsr;
                HC_SyntaxAnalyserCreateExpressions(analyser, &ci);
                leftPnsr = rightPnsr + 1; /* ignore next semi colon */
                break;
            }
            case HC_LEXICAL_TOKENS_LEFT_CURLY_BRACKET:
            {
                scope++;
                break;
            }
            case HC_LEXICAL_TOKENS_RIGHT_CURLY_BRACKET:
            {
                if (scope == 0)
                {
                    printf("Syntax error [line %d: index %d]: trying to dereference scope, %s detected\n", current->Line, current->LineOffset + 1, current->Source);
                    return HC_False;
                }
                scope--;
                break;
            }
            default:
                goto update;
        }

        update:
        {
            if (i == analyser->AnalysingCount)
                break;

            i++;
        }

    }

    return HC_True;
}
U8 HC_SyntaxAnalyserDestroy(HC_SyntaxAnalyser *analyser)
{
    free(analyser->Errors);
    free(analyser->Analysing);
    return HC_True;
}