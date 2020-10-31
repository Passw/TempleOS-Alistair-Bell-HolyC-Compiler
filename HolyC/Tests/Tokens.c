#include <HolyC-SDK/SDK.h>

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
    HC_Token t;
    HC_Lexer l = *(HC_Lexer *)data;

    I64 i;
    for (i = 0; i < sizeof(tokens) / sizeof(const I8 *); i++)
    {
        U8 result = HC_TokenFromString(&l, &t, tokens[i]);
        if (!result && t.Token == HC_LEXICAL_TOKENS_INVALID)
            return HC_False;
    }
    return HC_True;
}

U32 main()
{
    HC_Lexer l;
    HC_LexerCreateInfo lc;
    memset(&lc, 0, sizeof(HC_LexerCreateInfo));
    HC_LexerCreate(&l, &lc);
    HC_LexerLoadStream(&l, &(HC_LexerLoadStreamInfo){.Input = "Tests/Main.IC" });

    HC_TestCreateInfo tests[] =
    {
        {.Assertion = HC_False, .Callback = TokenTest, .ExpectedResult = HC_True, .TestName = "Tokenization & hashing test", .FailMessage = "Tokenization has failed", .ProgramData = &l },
    };


    HC_TestRuntineInfo runtime;
    U8 result = HC_TestRunTest(tests, sizeof(tests) / sizeof(HC_TestCreateInfo), &runtime);


    HC_LexerDestroy(&l);
    return result;
}