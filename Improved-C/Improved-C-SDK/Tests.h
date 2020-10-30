#ifndef TESTS_H
#define TESTS_H

#include "Common.h"

typedef struct IC_TestCreateInfo IC_TestCreateInfo;

typedef U8 (*IC_TestCallback)(void *);

typedef struct IC_TestCreateInfo
{
    U8              Assertion;
    const U8        *TestName;
    const U8        *FailMessage;
    void            *ProgramData;
    U8              ExpectedResult;
    IC_TestCallback Callback;
} IC_TestCreateInfo;

typedef struct IC_TestRuntineInfo
{
    U64             SuccesCount;
    U64             FailCount;
} IC_TestRuntineInfo; 

extern U8 IC_TestRunTest(IC_TestCreateInfo *infos, U64 count, IC_TestRuntineInfo *runtime);

#endif