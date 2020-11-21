#include "Compiler.h"

U8 HC_CompilerCreate(HC_Compiler *compiler, HC_CompilerCreateInfo *info)
{
    assert(compiler != NULL);
    assert(info != NULL);

    HC_LexerCreate(&compiler->Lexer, &info->LexerInfo);
    return HC_True;
}
U8 HC_CompilerRun(HC_Compiler *compiler)
{
    U64 i;
    for (i = 0; i < compiler->Lexer.FileCount; i++)
    {
        compiler->Lexer.CurrentFile = &compiler->Lexer.Files[i];
        if (!HC_LexerParse(&compiler->Lexer))
            return HC_False;
    }
    HC_SyntaxAnalyserCreate(&compiler->Analyser, &(HC_SyntaxAnalyserCreateInfo) { .Lexer = &compiler->Lexer });
    if (!HC_SyntaxAnalyserAnalyse(&compiler->Analyser))
    {
        printf("Failed to analyse %s\n", compiler->Lexer.CurrentFile->FileName);
        return HC_False;
    }
    return HC_True;
}
U8 HC_CompilerDestroy(HC_Compiler *compiler)
{
    assert(compiler != NULL);
    HC_LexerDestroy(&compiler->Lexer);
    HC_SyntaxAnalyserDestroy(&compiler->Analyser);
    return HC_True;
}