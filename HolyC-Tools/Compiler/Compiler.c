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
    if (!HC_LexerParse(&compiler->Lexer))
        return HC_False;
   
    HC_SyntaxAnalyserCreate(&compiler->Analyser, &(HC_SyntaxAnalyserCreateInfo) { .Lexer = &compiler->Lexer });
    if (!HC_SyntaxAnalyserAnalyse(&compiler->Analyser))
        return HC_False;
    return HC_True;
}
U8 HC_CompilerDestroy(HC_Compiler *compiler)
{
    assert(compiler != NULL);
    HC_LexerDestroy(&compiler->Lexer);
    HC_SyntaxAnalyserDestroy(&compiler->Analyser);
    return HC_True;
}
