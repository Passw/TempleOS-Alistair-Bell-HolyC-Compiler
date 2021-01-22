#include <Core-Backend/SDK.h>

static U8 TokenWhitespace(U0 *data)
{
    HC_Lexer l = *(HC_Lexer *)data;

    HC_LexerParse(&l);

    U64 i = 0;
    U32 j = 0;
    HC_Token *t;
    for (i = 0; i < l.File->TokenCount; i++)
    {
        t = &l.File->Tokens[i];
        const char *src = t->Source;
        if (strlen(src) >= 1 && src[0] == HC_LexerCheckTerminationCharacterOrWhitespace(src[0], &j))
        {
            printf("Whitespace character present [line %d]: %s\n", t->Line, t->Source);
            return HC_False;
        }
        printf("[%2lu][%s]\n", i, t->Source);
    }
    return HC_True;
}
I32 main()
{
    HC_Lexer l;
    memset(&l, 0, sizeof(HC_Lexer));
    
    HC_LexerCreateInfo ci;
    memset(&ci, 0, sizeof(HC_LexerCreateInfo));
    ci.Loading = (HC_LexerLoadStreamInfo) { .Input = "../../../Tests/NoWhitespaceMain.HC" };
    if (!HC_LexerCreate(&l, &ci))
        return 1;
    

    HC_TestCreateInfo tests[1];
    tests[0].TestName       = "Tokenization whitespace test (Tests/NoWhitespaceMain.HC)";
    tests[0].FailMessage    = "Tokenization has failed";
    tests[0].Callback       = TokenWhitespace;
    tests[0].ExpectedResult = HC_True;
    tests[0].Assertion      = HC_False;
    tests[0].ProgramData    = &l;

    /*
    tests[1].TestName       = "Token Striper test (Tests/Comment.HC)";
    tests[1].FailMessage    = "Token striping has failed";
    tests[1].Callback       = TokenComment;
    tests[1].ExpectedResult = HC_True;
    tests[1].Assertion      = HC_False;
    tests[1].ProgramData    = &l;
    */

    HC_TestRuntineInfo runtime;
    U8 result = HC_TestRunTest(tests, sizeof(tests) / sizeof(HC_TestCreateInfo), &runtime);
    HC_LexerDestroy(&l);
    return result;
}
