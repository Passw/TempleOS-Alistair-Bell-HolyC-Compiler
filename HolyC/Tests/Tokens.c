#include <Core-Backend/SDK.h>

static U8 TokenTest(U0 *data)
{
    HC_Lexer l = *(HC_Lexer *)data;
    I64 i;
    for (i = 0; i < l.Files[0].TokenCount; i++)
    {
        const I8 *src = l.CurrentFile->Tokens[i].Source;
        if (strlen(src) >= 1 && src[0] == HC_LexerCheckTerminationCharacterOrWhitespace(src[0]))
            return HC_False;
        printf("[%2lu][%s]\n", i, l.Files[0].Tokens[i].Source);
    }    
    return HC_True;
}

U32 main()
{
    HC_Lexer l;
    memset(&l, 0, sizeof(HC_Lexer));
    
    HC_LexerCreateInfo ci;
    memset(&ci, 0, sizeof(HC_LexerCreateInfo));
    ci.LoadCount = 1;
    ci.Loads     = &(HC_LexerLoadStreamInfo) { .Input = "Tests/NoWhitespaceMain.HC" };
    HC_LexerCreate(&l, &ci);

    HC_TestCreateInfo tests[1];
    tests[0].Assertion = HC_False;
    tests[0].Callback = TokenTest;
    tests[0].ExpectedResult = HC_True;
    tests[0].TestName = "Tokenization Test (Tests/NoWhitespaceMain.HC)";
    tests[0].FailMessage = "Tokenization has failed";
    tests[0].ProgramData = &l;

    HC_TestRuntineInfo runtime;
    U8 result = HC_TestRunTest(tests, sizeof(tests) / sizeof(HC_TestCreateInfo), &runtime);


    HC_LexerDestroy(&l);
    return result;
}
