#include <HolyC-SDK/SDK.h>

static U8 FailTest(void *data)
{
    return HC_False;
}

I32 main()
{
    HC_TestCreateInfo tests[] = 
    {
        (HC_TestCreateInfo) { .Assertion = HC_False, .Callback = FailTest, .ExpectedResult = HC_True, .TestName = "Fail test", .FailMessage = "Test has succesfully failed", .ProgramData = NULL }
    };
    HC_TestRuntineInfo runtime;

    HC_TestRunTest(tests, sizeof(tests) / sizeof(HC_TestCreateInfo), &runtime);


    return HC_True;
}