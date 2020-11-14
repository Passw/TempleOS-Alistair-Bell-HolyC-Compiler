#include "Analyser.h"

static U0 HC_SyntaxAnalyserPrintTokens(HC_SyntaxAnalyser *analyser)
{
    U64 i;
    for (i = 0; i < analyser->AnalysingCount; i++)
        printf("[%3lu][%s]\n", i, analyser->Analysing[i].Source);
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


    HC_SyntaxAnalyserPrintTokens(analyser);



    return HC_True;
}
U8 HC_SyntaxAnalyserDestroy(HC_SyntaxAnalyser *analyser)
{
    free(analyser->Errors);
    free(analyser->Analysing);
    return HC_True;
}