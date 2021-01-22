#ifndef TESTS_H
#define TESTS_H

#include "Common.h"

typedef struct HC_TestCreateInfo HC_TestCreateInfo;

typedef U8 (*HC_TestCallback)(U0 *);

typedef struct HC_TestCreateInfo
{
    U8              Assertion;
    const char      *TestName;
    const char      *FailMessage;
    U0              *ProgramData;
    U8              ExpectedResult;
    HC_TestCallback Callback;
} HC_TestCreateInfo;

typedef struct HC_TestRuntineInfo
{
    U64             SuccessCount;
    U64             FailCount;
} HC_TestRuntineInfo; 

extern U8 HC_TestRunTest(HC_TestCreateInfo *infos, U64 count, HC_TestRuntineInfo *runtime);

#endif
