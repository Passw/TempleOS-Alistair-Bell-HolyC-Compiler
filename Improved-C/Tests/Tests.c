#include <Improved-C-SDK/SDK.h>

static U8 FailTest(void *data)
{
    return IC_False;
}

I32 main()
{
    IC_TestCreateInfo tests[] = 
    {
        (IC_TestCreateInfo) { .Assertion = IC_False, .Callback = FailTest, .ExpectedResult = IC_True, .TestName = "Fail test", .FailMessage = "Test has succesfully failed", .ProgramData = NULL }
    };
    IC_TestRuntineInfo runtime;

    IC_TestRunTest(tests, sizeof(tests) / sizeof(IC_TestCreateInfo), &runtime);


    return IC_True;
}