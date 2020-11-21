#include "Analyser.h"

/*
    All warnings and errors are treated as fatal
    Good code has no warnings, its the programers problem to fix the warnings
    Its lazy to ignore warnings, that is why cmake uses -Wfatal
*/

typedef struct HC_SyntaxAnalyserExpressionCreateInfo
{
    U64 Offset;
    U64 Count;
    U16 Scope;
} HC_SyntaxAnalyserExpressionCreateInfo;

static inline U0 HC_QuickSort(U64 *numbers, const U64 first, const U64 last)
{
    U64 i, j, pivot, temp;
    if (0 < last)
    {
        pivot = first;
        i     = first;
        j     = last;
        
        while (i < j)
        {
            while (numbers[i] <= numbers[pivot]&& i < last)
            {
                i++;
                while(numbers[j] > numbers[pivot])
                {
                    j--;
                    if(i < j)
                    {
                        temp       = numbers[i];
                        numbers[i] = numbers[j];
                        numbers[j] = temp;
                    }
                }
            }
        }

        temp            = numbers[pivot];
        numbers[pivot]  = numbers[j];
        numbers[j]      = temp;
        HC_QuickSort(numbers, first, j - 1);
        HC_QuickSort(numbers, j + 1, last);
    }
}
static inline I64 HC_BinarySearchHash(HC_SyntaxAnalyserSymbol *symbols, U64 low, U64 high, U64 searching)
{
    printf("%lu %lu %lu\n", low, high, searching);
    if (low <= high)
	{
		U64 mid = low + (high - low) / 2;
		if (searching == symbols[mid].ReferenceHash)
			return mid;
		
        else if (searching < symbols[mid].ReferenceHash)
			return HC_BinarySearchHash(symbols, low, mid - 1, searching);
		
        else
			return HC_BinarySearchHash(symbols, mid + 1, high, searching);
	}
	return -1;
}
static U8 HC_SyntaxAnalyserCheckRepeatedSymbol(HC_SyntaxAnalyser *analyser, U16 scope, U64 hash)
{
    HC_SyntaxAnalyserSymbolTable *t = &analyser->SymbolTables[scope - 1];
    switch (t->Count)
    {
        case 0:
            return HC_False;
        case 1:
            return (t->Symbols[0].ReferenceHash == hash);
        default:
            return (HC_BinarySearchHash(t->Symbols, 0, t->Count, hash) != -1);
    }
    
    return 1;
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
static U8 HC_SyntaxAnalyserUnderstandMethod(HC_SyntaxAnalyser *analyser, HC_SyntaxAnalyserExpressionCreateInfo *info)
{   
    U64 i = 0;
    
    if (info->Count == 0)
        return HC_False;
    
    HC_Token *t = &analyser->Analysing[info->Offset + i];
    while (i < info->Count)
    {
        printf("%s\n", t->Source);
        
        
        /* Incrimenter */
        t++;
        i++;
    }
    

    return HC_True;
}


static U8 HC_SyntaxAnalyserCreateExpressions(HC_SyntaxAnalyser *analyser, HC_SyntaxAnalyserExpressionCreateInfo *info)
{
    HC_Token *indexer = &analyser->Analysing[info->Offset];
    HC_Token type;

    /* Check built in type */
    if (HC_SyntaxAnalyserCheckBuiltInType(indexer->Hash))
    {
        if (info->Count == 1)
            goto expectedExpression;

        type = *indexer;
        indexer++;

        /* Check repetition */
        if (HC_SyntaxAnalyserCheckBuiltInType(indexer->Hash) || HC_SyntaxAnalyserCheckRepeatedSymbol(analyser, info->Scope, indexer->Hash))
        {
            return (HC_ErrorRedefinedSymbol(&(HC_ErrorCreateInfo) { .Causation = indexer, .Scope = info->Scope }));
        }
        else
        {
            HC_SyntaxAnalyserAddSymbol(analyser, &(HC_SyntaxAnalyserSymbolCreateInfo) { .SymbolToken = *indexer, .SymbolToken = type, .Scope = info->Scope } );
            //HC_Token name = *indexer;

            if (2 < info->Count)
            {
                indexer++;
                switch (indexer->Hash)
                {
                    /* Assignment declaration */
                    case HC_LEXICAL_TOKENS_EQUALS_STRING_HASH:
                    {
                        if (info->Count == 3)
                            goto expectedExpression;
                        indexer++;
                        
                        if (HC_SyntaxAnalyserCheckBuiltInType(indexer->Hash))
                            goto expectedExpression;
                        break;
                    }
                    case HC_LEXICAL_TOKENS_LEFT_PARAM_STRING_HASH:
                    {
                        HC_SyntaxAnalyserExpressionCreateInfo ci;
                        ci.Offset = info->Offset + 3;
                        ci.Count  = info->Count - 3;
                        HC_SyntaxAnalyserUnderstandMethod(analyser, &ci);
                        break;
                    }

                    default:
                       goto expectedExpression;
                }
            }
            else
            {
                goto end;
            }

        }
    }

    goto end;


    expectedExpression:
    {
        return (HC_ErrorExpectedExpression(&(HC_ErrorCreateInfo) { .Causation = indexer, .Scope = info->Scope }));
    }


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
    analyser->SymbolTables[0].Scope   = 0; /* Universal global scope */

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
    U16 scope     = 0;

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
                ci.Scope  = scope;
                if (HC_SyntaxAnalyserCreateExpressions(analyser, &ci) == HC_False)
                    return HC_False;

                leftPnsr = rightPnsr + 1; /* ignore next semi colon */
                break;
            }
            case HC_LEXICAL_TOKENS_LEFT_CURLY_BRACKET:
            {
                analyser->SymbolTables = realloc(analyser->SymbolTables, sizeof(HC_SyntaxAnalyserSymbolTable) * (scope + 1));
                scope++;
                break;
            }
            case HC_LEXICAL_TOKENS_RIGHT_CURLY_BRACKET:
            {
                if (scope == 0)
                    return (HC_ErrorDereferencedLowestScope(&(HC_ErrorCreateInfo) { .Line = current->Line }));
                
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