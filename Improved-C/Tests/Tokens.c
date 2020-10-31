#include <Improved-C-SDK/SDK.h>

U8 TokenTest(void *data)
{
    const I8 *tokens[] = 
    {
        ";",
        "+",
        "-",
        "/",
        "*",
        "=",
        
        "U0",
        "I8",
        "U8",
        "I16",
        "U16",
        "I32",
        "U32",
        "I64",
        "U64",
        "F32",
        "F64",
        "foo"
    };
    IC_Token t;
    IC_Lexer l = *(IC_Lexer *)data;

    I64 i;
    for (i = 0; i < sizeof(tokens) / sizeof(const I8 *); i++)
    {
        U8 result = IC_TokenFromString(&l, &t, tokens[i]);
        if (!result && t.Token == IC_LEXICAL_TOKENS_INVALID)
            return IC_False;
    }
    return IC_True;
}

U32 main()
{
    IC_Lexer l;
    IC_LexerCreateInfo lc;
    memset(&lc, 0, sizeof(IC_LexerCreateInfo));
    IC_LexerCreate(&l, &lc);
    IC_LexerLoadStream(&l, &(IC_LexerLoadStreamInfo){.Input = "Tests/Main.IC" });

    IC_TestCreateInfo tests[] =
    {
        {.Assertion = IC_False, .Callback = TokenTest, .ExpectedResult = IC_True, .TestName = "Tokenization & hashing test", .FailMessage = "Tokenization has failed", .ProgramData = &l },
    };


    IC_TestRuntineInfo runtime;
    U8 result = IC_TestRunTest(tests, sizeof(tests) / sizeof(IC_TestCreateInfo), &runtime);


    IC_LexerDestroy(&l);
    return result;
}