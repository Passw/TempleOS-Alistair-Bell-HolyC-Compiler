#ifndef ERROR_H
#define ERROR_H

#include "Common.h"
#include "Tokens.h"

typedef enum HC_ErrorType
{
    HC_ERROR_TYPE_WARNING,
    HC_ERROR_TYPE_FATAL_ERROR,
} HC_ErrorType;

typedef struct HC_Error
{
    HC_ErrorType Type;
    HC_Token     *Reference;
} HC_Error;

#endif