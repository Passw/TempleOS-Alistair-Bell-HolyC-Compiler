#ifndef ANALYSER_H
#define ANALYSER_H

#include "Common.h"
#include "Tokens.h"
#include "Errors.h"
#include "Stream.h"
#include "Lexer.h"

typedef struct HC_Lexer HC_Lexer;

typedef struct HC_SyntaxAnalyser
{
    const I8    *StreamName;
    HC_Token    *Analysing;
    HC_Error    *Errors;
    U64         Count;
    U64         ErrorCount;
} HC_SyntaxAnalyser;

typedef struct HC_SyntaxAnalyserCreateInfo
{
    HC_Lexer    *Lexer;
} HC_SyntaxAnalyserCreateInfo;

extern U8 HC_SyntaxAnalyserCreate(HC_SyntaxAnalyser *analyser, HC_SyntaxAnalyserCreateInfo *createInfo);
extern U8 HC_SyntaxAnalyserAnalyse(HC_SyntaxAnalyser *analyser);
extern U8 HC_SyntaxAnalyserDestroy(HC_SyntaxAnalyser *analyser);

#endif