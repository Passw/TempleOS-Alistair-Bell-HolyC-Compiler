#include "Analyser.h"

U8 HC_SyntaxAnalyserCreate(HC_SyntaxAnalyser *analyser, HC_SyntaxAnalyserCreateInfo *createInfo)
{
    assert(analyser != NULL);
    assert(createInfo != NULL);

    memset(analyser, 0, sizeof(HC_SyntaxAnalyser));
    HC_Lexer *l = createInfo->Lexer;

    analyser->StreamName = l->CurrentFile->FileName;
    analyser->Errors = calloc(0, sizeof(HC_Error));
    
    U64 tc = l->CurrentFile->TokenCount;

    analyser->Analysing = calloc(l->CurrentFile->TokenCount, sizeof(HC_Token));
    memcpy(analyser->Analysing, l->CurrentFile->Tokens, tc * sizeof(HC_Token));
    return HC_True;
}
U8 HC_SyntaxAnalyserDestroy(HC_SyntaxAnalyser *analyser)
{
    free(analyser->Errors);
    free(analyser->Analysing);
    return HC_True;
}