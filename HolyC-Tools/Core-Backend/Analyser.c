#include "Analyser.h"

typedef struct HC_SyntaxAnalyserExpressionCreateInfo
{
    U64 Offset;
    U64 Count;
    U16 Scope;
} HC_SyntaxAnalyserExpressionCreateInfo;

typedef struct HC_SyntaxAnalyserValidateNextTokenInfo
{
    HC_Token    *Current;
    HC_Token    *Next;
    U64         StatusFlags;
} HC_SyntaxAnalyserValidateNextTokenInfo;

typedef enum HC_SyntaxAnalyserStepThroughFlags
{
    HC_SYNTAX_ANALYSER_STEP_THROUGH_FLAGS_PREVIOUS_TYPE_DECLARATION     = 0x1,
    HC_SYNTAX_ANALYSER_STEP_THROUGH_FLAGS_PREVIOUS_SYMBOL_REFERENCE     = 0x2,
    HC_SYNTAX_ANALYSER_STEP_THROUGH_FLAGS_PREVIOUS_KEYWORD_REFERENCE    = 0x4,
    HC_SYNTAX_ANALYSER_STEP_THROUGH_FLAGS_STARTING_METHOD_DECLARATION   = 0x8,
} HC_SyntaxAnalyserStepThroughFlags;

static inline U8 HC_SyntaxAnalyserValidateNextToken(HC_SyntaxAnalyser *analyser, HC_SyntaxAnalyserValidateNextTokenInfo *info)
{
    HC_Token *errorRef = info->Current;

    switch (info->Current->Token)
    {
        case HC_LEXICAL_TOKEN_TYPES:
        {
            if (info->Next != NULL && info->Next->Token == HC_LEXICAL_TOKEN_TYPES)
            {
                errorRef = info->Next;
                goto expectedExpression;
            }
            break;
        }
        default:
        {
            break;
        }

    }

    return HC_True;


    expectedExpression:
        return HC_ErrorExpectedExpression(&(HC_ErrorCreateInfo) { .Causation = errorRef, .Line = errorRef->Line });
}
static U8 HC_SyntaxAnalyserCreateExpressions(HC_SyntaxAnalyser *analyser, HC_SyntaxAnalyserExpressionCreateInfo *info)
{
    HC_Token *iterator = &analyser->Analysing[info->Offset];
    switch (info->Count)
    {
        case 0: goto expectedExpression; break;
    }
    
    U64 i;
    U64 stepThroughFlags = 0;

    for (i = 0; i < info->Count; i++)
    {
        switch (iterator->Token)
        {
            case HC_LEXICAL_TOKEN_TYPES:
            {
                stepThroughFlags |= HC_SYNTAX_ANALYSER_STEP_THROUGH_FLAGS_PREVIOUS_TYPE_DECLARATION;
                break;
            }
            case HC_LEXICAL_TOKEN_KEYWORD:
            {
                stepThroughFlags |= HC_SYNTAX_ANALYSER_STEP_THROUGH_FLAGS_PREVIOUS_KEYWORD_REFERENCE;
                break;
            }
            case HC_LEXICAL_TOKEN_UNRESOLVED:
            {
                
            }
            default:
            {
                break;
            }

        }

        HC_SyntaxAnalyserValidateNextTokenInfo vinfo;
        memset(&vinfo, 0, sizeof(HC_SyntaxAnalyserValidateNextTokenInfo));
        vinfo.Current            = iterator;
        vinfo.StatusFlags        = stepThroughFlags;

        if (i < (info->Count - 1))
            vinfo.Next          = &analyser->Analysing[info->Offset + (i + 1)];

        if (!HC_SyntaxAnalyserValidateNextToken(analyser, &vinfo))
            return HC_False;
        iterator++;
    }

    goto end;

    expectedExpression:
        return HC_ErrorExpectedExpression(&(HC_ErrorCreateInfo) { .Causation = iterator, .Line = iterator->Line, .Scope = info->Scope });

    end:
        return HC_True;
}
U8 HC_SyntaxAnalyserAddSymbol(HC_SyntaxAnalyser *analyser, HC_SyntaxAnalyserSymbolCreateInfo *info)
{
    HC_SyntaxAnalyserSymbol s;
    HC_SyntaxAnalyserSymbolTable *t = &analyser->SymbolTables[info->Scope];
    s.ReferenceHash = info->SymbolToken.Hash;
    s.TypeHash      = info->PreviousToken.Hash;
    analyser->SymbolTables[info->Scope].Symbols = realloc(analyser->SymbolTables[info->Scope].Symbols, sizeof(HC_SyntaxAnalyserSymbol) * (t->Count + 1));
    memcpy(&t->Symbols[t->Count], &s, sizeof(HC_SyntaxAnalyserSymbol));
    
    t->Count++;
    return HC_True;
}

U8 HC_SyntaxAnalyserCreate(HC_SyntaxAnalyser *analyser, HC_SyntaxAnalyserCreateInfo *createInfo)
{
    assert(analyser != NULL);
    assert(createInfo != NULL);

    memset(analyser, 0, sizeof(HC_SyntaxAnalyser));
    HC_Lexer *l = createInfo->Lexer;

    analyser->StreamName = l->CurrentFile->FileName;
    analyser->AnalysingCount = l->CurrentFile->TokenCount;
    analyser->SymbolTables = calloc(1, sizeof(HC_SyntaxAnalyserSymbolTable));
    analyser->TableCount   = 1;

    /* Global table */
    memset(&analyser->SymbolTables[0], 0, sizeof(HC_SyntaxAnalyserSymbolTable));
    analyser->SymbolTables[0].Symbols = calloc(0, sizeof(HC_SyntaxAnalyserSymbol));
    
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
    
    U64 i                       = 0;
    U64 leftPnsr                = 0;
    U64 rightPnsr               = 0;
    U16 scope                   = 0;
    HC_Token *lastNewScope      = NULL;
    
    while (HC_True)
    {
        rightPnsr = i;
        HC_Token *current = &analyser->Analysing[i];
        switch (current->Hash)
        {
            case HC_LEXICAL_TOKENS_SEMI_COLON_STRING_HASH:
            {
                HC_SyntaxAnalyserExpressionCreateInfo ci;
                ci.Count  = (rightPnsr - leftPnsr);
                ci.Offset = leftPnsr;
                ci.Scope  = scope;
                if (!HC_SyntaxAnalyserCreateExpressions(analyser, &ci))
                    return HC_False;

                leftPnsr = rightPnsr + 1; /* ignore next semi colon */
                break;
            }
            case HC_LEXICAL_TOKENS_LEFT_CURLY_BRACKET_STRING_HASH:
            {
                scope++;
                analyser->SymbolTables = realloc(analyser->SymbolTables, sizeof(HC_SyntaxAnalyserSymbolTable) * (scope + 1));
                analyser->SymbolTables[scope].Symbols = calloc(0, sizeof(HC_SyntaxAnalyserSymbol));
                lastNewScope = &analyser->Analysing[i];
                break;
            }
            case HC_LEXICAL_TOKENS_RIGHT_CURLY_BRACKET_STRING_HASH:
            {
                if (scope == 0)
                    return (HC_ErrorDereferencedLowestScope(&(HC_ErrorCreateInfo) { .Line = (U64)current->Line }));
                
                free(analyser->SymbolTables[scope].Symbols);
                analyser->SymbolTables = realloc(analyser->SymbolTables, sizeof(HC_SyntaxAnalyserSymbolTable) * (scope + 1));
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

    if (0 < scope)
        return HC_ErrorUnDereferencedTopScope(&(HC_ErrorCreateInfo) { .Scope = scope, .Causation = lastNewScope });

    return HC_True;
}
U8 HC_SyntaxAnalyserDestroy(HC_SyntaxAnalyser *analyser)
{
    U64 i;
    for (i = 0; i < analyser->TableCount; i++)
        free(analyser->SymbolTables[i].Symbols);
    free(analyser->SymbolTables);
    free(analyser->Analysing);
    return HC_True;
}