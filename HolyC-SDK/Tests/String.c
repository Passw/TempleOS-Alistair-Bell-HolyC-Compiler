#include <Core-Backend/SDK.h>
#include "ExternalReferences.h"

U8 StrLenTest(U0 *data)
{


    return HC_True;
}

U32 main(I32 argumentCount, I8 *arguments)
{
    HC_TestCreateInfo tests[1];
    tests[0].TestName       = "Amd64 assembly function: StrLen";
    tests[0].FailMessage    = "Amd64 assembly function: StrLen has failed to give correct length";
    tests[0].Callback       = StrLenTest;
    tests[0].ExpectedResult = HC_True;
    tests[0].Assertion      = HC_False;
    tests[0].ProgramData    = NULL;


    HC_TestRuntineInfo runtimeInfo;
    memset(&runtimeInfo, 0, sizeof(HC_TestRuntineInfo));
    HC_TestRunTest(tests, sizeof(tests) / sizeof(HC_TestCreateInfo), &runtimeInfo);

    return HC_True;
}