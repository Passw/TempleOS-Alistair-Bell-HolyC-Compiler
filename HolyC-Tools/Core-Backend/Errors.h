#ifndef ERRORS_H
#define ERRORS_H

#include "Common.h"
#include "Tokens.h"

typedef struct HC_ErrorCreateInfo
{
    U16         Scope;
    U64         Line; /* Used for dereferenced scope */
    HC_Token    *Causation;
} HC_ErrorCreateInfo;

extern U8 HC_ErrorExpectedExpression(HC_ErrorCreateInfo *info);
extern U8 HC_ErrorUnDereferencedTopScope(HC_ErrorCreateInfo *info);
extern U8 HC_ErrorDereferencedLowestScope(HC_ErrorCreateInfo *info);
extern U8 HC_ErrorRedefinedSymbol(HC_ErrorCreateInfo *info);

#endif