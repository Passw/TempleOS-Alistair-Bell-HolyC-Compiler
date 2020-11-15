#ifndef COMPILER_H
#define COMPILER_H

#include <Core-Backend/SDK.h>

typedef struct HC_Compiler
{
    HC_Lexer            Lexer;
    HC_SyntaxAnalyser  Analyser;
} HC_Compiler;

typedef struct HC_CompilerCreateInfo
{
    HC_LexerCreateInfo LexerInfo;
} HC_CompilerCreateInfo;

extern U8 HC_CompilerCreate(HC_Compiler *compiler, HC_CompilerCreateInfo *info);
extern U8 HC_CompilerRun(HC_Compiler *compiler);
extern U8 HC_CompilerDestroy(HC_Compiler *compiler);


#endif