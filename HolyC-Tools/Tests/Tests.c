#include <Core-Backend/SDK.h>

static U8 FailTest(U0 *data)
{
    return HC_False;
}

I32 main()
{
    HC_TestCreateInfo tests[1];
    tests[0].TestName = "Fail test";
    tests[0].FailMessage = "Test has failed successfully";
    tests[0].ProgramData = NULL;
    tests[0].Assertion = HC_False;
    tests[0].Callback = FailTest;
    tests[0].ExpectedResult = HC_True;

    HC_TestRuntineInfo runtime;

    return !(HC_TestRunTest(tests, sizeof(tests) / sizeof(HC_TestCreateInfo), &runtime));
}
