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
static U8 HC_SyntaxAnalyserCreateExpressions(HC_SyntaxAnalyser *analyser, HC_SyntaxAnalyserExpressionCreateInfo *info)
{
    U64 i;
    for (i = 0; i < info->Count; i++)
        printf("[%lu][%s]\n", i, analyser->Analysing[i + info->Offset].Source);
    printf("\n");
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
    
    U64 builtInCount;
    HC_DataType builtInTypes[9];

    HC_DataTypesGetDefault(builtInTypes, &builtInCount, HC_False);
    printf("Loaded %lu default values\n", builtInCount);

    if (analyser->AnalysingCount <= 1)
    {
        printf("Expected expression!\n");
        return HC_False;
    }
    
    U64 i         = 0;
    U64 leftPnsr  = 0;
    U64 rightPnsr = 0;

    while (HC_True)
    {
        rightPnsr = i;
        HC_Token *current = &analyser->Analysing[i];
        if (current->Token == HC_LEXICAL_TOKENS_SEMI_COLON)
        {
            HC_SyntaxAnalyserExpressionCreateInfo ci;
            ci.Count  = (rightPnsr - leftPnsr);
            ci.Offset = leftPnsr;
            HC_SyntaxAnalyserCreateExpressions(analyser, &ci);
            leftPnsr = rightPnsr + 1; /* ignore next semi colon */
        }

        if (i == analyser->AnalysingCount)
            break;

        i++;
    }

    return HC_True;
}
U8 HC_SyntaxAnalyserDestroy(HC_SyntaxAnalyser *analyser)
{
    free(analyser->Errors);
    free(analyser->Analysing);
    return HC_True;
}