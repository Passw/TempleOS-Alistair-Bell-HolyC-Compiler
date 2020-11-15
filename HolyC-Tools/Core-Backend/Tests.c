#include "Tests.h"

static U8 HC_TestExecute(HC_TestCreateInfo *info)
{
   return info->Callback(info->ProgramData);
}

U8 HC_TestRunTest(HC_TestCreateInfo *infos, U64 count, HC_TestRuntineInfo *runtime)
{
    assert(infos != NULL);
    assert(runtime != NULL);
    memset(runtime, 0, sizeof(HC_TestRuntineInfo));

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
            assert(current->TestName != NULL); /* requires a name */
            printf("Test %lu %s has failed\n", i + 1, current->TestName);
            if (current->FailMessage == NULL)
                printf("%s has failed\n", current->TestName);
            else
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
    
    F32 successPercentage = ((F32)runtime->SuccessCount / count) * 100;
    printf("Ran %lu test(s), success rate %.2f%%\n", count, successPercentage);
    printf("%s\n\n", line);
    return HC_True;
}
