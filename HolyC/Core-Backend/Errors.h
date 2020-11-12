#ifndef ERROR_H
#define ERROR_H

#include "Common.h"
#include "Tokens.h"

typedef struct HC_Error
{
    U8 Fatal;
    HC_Token *Referene;
} HC_Error;


#endif