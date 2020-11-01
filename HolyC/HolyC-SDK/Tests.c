#include "Tests.h"

static U8 HC_TestExecute(HC_TestCreateInfo *info)
{
   U8 result = info->Callback(info->ProgramData);
}

U8 HC_TestRunTest(HC_TestCreateInfo *infos, U64 count, HC_TestRuntineInfo *runtime)
{
    assert(infos != NULL);
    assert(runtime != NULL);
    
    if (count <= 0)
    {
        printf("No tests specified\n");
        return HC_True;
    }
    
    U64 i;
    printf("Running %lu tests\n", count);
    const I8 *line = "------------------------------------------";
    for (i = 0; i < count; i++)
    {
        HC_TestCreateInfo *current = &infos[i];
        printf("\tRunning test %lu: %s\n", i + 1, current->TestName);
        printf("%s\n", line);

        U8 testResult = HC_TestExecute(current);

        if (testResult != current->ExpectedResult)
        {
            printf("Test %lu %s has failed\n", i + 1, current->TestName);
            printf("%s\n", current->FailMessage);

            if (current->Assertion)
                assert(testResult != current->ExpectedResult);
            runtime->FailCount++;
        }
        else
        {
            printf("Test %s passed without errors (expected result achieved)\n", infos->TestName);
            runtime->SuccessCount++;
        }
        printf("%s\n", line);
    }
    return HC_True;
}
