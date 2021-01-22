#include <Core-Backend/SDK.h>

static U8 SameHashResult(U0 *data)
{
    const char *buffer = "HelloWorld";
    U64 hash1 = HC_TokenHashString(buffer);
    U64 hash2 = HC_TokenHashString(buffer);

    if (hash1 != hash2)
    {
        printf("Expected hash to be the same from [%lu != %lu]\n", hash1, hash2);
        return HC_False;
    }
    const char *newBuffer = "Hello World";
    U64 hash3 = HC_TokenHashString(newBuffer);

    if (hash1 == hash3 || hash2 == hash3)
    {
        printf("Expected hash to be different [%lu | %lu == %lu]", hash1, hash2, hash3);
        return HC_False;
    }
    return HC_True;
}

I32 main(U0)
{
    HC_TestCreateInfo tests[1];
    tests[0].TestName          = "Same char buffer hashing test";
    tests[0].FailMessage       = NULL;
    tests[0].ProgramData       = NULL;
    tests[0].ExpectedResult    = HC_True;
    tests[0].Assertion         = HC_False;
    tests[0].Callback          = SameHashResult;

    HC_TestRuntineInfo ri;
    
    
    return HC_TestRunTest(tests, sizeof(tests) / sizeof(HC_TestCreateInfo), &ri);
}
