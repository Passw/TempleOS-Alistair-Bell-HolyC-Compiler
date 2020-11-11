#ifndef ANALYSER_H
#define ANALYSER_H

#include "Common.h"
#include "Tokens.h"

typedef struct HC_Lexer HC_Lexer;

typedef struct HC_SyntaxAnalyser
{


} HC_SyntaxAnalyser;

typedef struct HC_SyntaxAnalyserCreateInfo
{
    HC_Token    *Analysing;
    U64         AnalysingCount;
} HC_SyntaxAnalyserCreateInfo;

extern U8 HC_SyntaxAnalyserCreate(HC_SyntaxAnalyser *analyser, HC_SyntaxAnalyserCreateInfo *createInfo);
extern U8 HC_SyntaxAnalyserAnalyse(HC_SyntaxAnalyser *analyser);

#endif