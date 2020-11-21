#include "Errors.h"

U8 HC_ErrorExpectedExpression(HC_ErrorCreateInfo *info)
{
    printf("Invalid syntax [line %d]: Expected expression after \'%s\'\n", info->Causation->Line, info->Causation->Source);
    return HC_False;
}
U8 HC_ErrorDereferencedLowestScope(HC_ErrorCreateInfo *info)
{
    printf("Invalid syntax [line %d]: Trying to dereference scope further than allowed\n", info->Scope);
    return HC_False;
}
U8 HC_ErrorRedefinedSymbol(HC_ErrorCreateInfo *info)
{
    printf("Invalid syntax [line %d]: Repetition of type or symbol declaration \'%s\'\n", info->Causation->Line, info->Causation->Source);
    return HC_False;
}