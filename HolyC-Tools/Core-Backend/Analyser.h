#ifndef ANALYSER_H
#define ANALYSER_H

#include "Common.h"
#include "Tokens.h"
#include "Stream.h"
#include "Lexer.h"
#include "Errors.h"

/* 
    Scopes

    U64 i = 10; 0 

    { 1
        { 2

            { 3

            } 3
        } 2
    } 1

*/

#define HC_ANALYSER_GLOBAL_SCOPE_REFERENCE 0 /* the largest smallest will be the value for global scopes */

typedef struct HC_SyntaxAnalyserSymbolCreateInfo
{
    U16             Scope;
    HC_Token        SymbolToken;
    HC_Token        PreviousToken;
} HC_SyntaxAnalyserSymbolCreateInfo;

typedef struct HC_SyntaxAnalyserSymbol
{
    U64         ReferenceHash;
    U64         TypeHash;
} HC_SyntaxAnalyserSymbol;

typedef struct HC_SyntaxAnalyserSymbolTable
{
    U16                         Scope;
    U32                         Count;
    HC_SyntaxAnalyserSymbol     *Symbols;
} HC_SyntaxAnalyserSymbolTable;

typedef struct HC_SyntaxAnalyser
{
    const I8                       *StreamName;
    HC_Token                       *Analysing;
    HC_SyntaxAnalyserSymbolTable   *SymbolTables;
    U16                             TableCount;
    U64                             AnalysingCount;
} HC_SyntaxAnalyser;

typedef struct HC_SyntaxAnalyserCreateInfo
{
    HC_Lexer    *Lexer;
} HC_SyntaxAnalyserCreateInfo;

extern U8 HC_SyntaxAnalyserCreate(HC_SyntaxAnalyser *analyser, HC_SyntaxAnalyserCreateInfo *createInfo);
extern U8 HC_SyntaxAnalyserAddSymbol(HC_SyntaxAnalyser *analyser, HC_SyntaxAnalyserSymbolCreateInfo *info);
extern U8 HC_SyntaxAnalyserAnalyse(HC_SyntaxAnalyser *analyser);
extern U8 HC_SyntaxAnalyserDestroy(HC_SyntaxAnalyser *analyser);

#endif