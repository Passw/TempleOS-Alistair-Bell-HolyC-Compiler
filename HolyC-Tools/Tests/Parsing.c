#include <Core-Backend/SDK.h>

U8 ParseInvalid(U0 *data)
{
    HC_Lexer l = (*(HC_Lexer *)data);
    l.CurrentFile = &l.Files[0];
    HC_LexerParse(&l);

    HC_SyntaxAnalyser a;
    HC_SyntaxAnalyserCreate(&a, &(HC_SyntaxAnalyserCreateInfo) { .Lexer = &l });

    U8 r = HC_SyntaxAnalyserAnalyse(&a);

    HC_SyntaxAnalyserDestroy(&a);
    return r;
}

U32 main()
{
    HC_Lexer l;
    HC_LexerCreateInfo ci;
    memset(&ci, 0, sizeof(HC_LexerCreateInfo));
    ci.LoadCount = 1;
    ci.Loads     = &(HC_LexerLoadStreamInfo) { .Input = "Tests/Errors/ExpectedExpressions.HC" };

    if (!HC_LexerCreate(&l, &ci))
        return HC_False;

    HC_TestCreateInfo tests[1];
    memset(tests, 0, sizeof(tests));

    tests[0].TestName       = "Parsing broken file (Tests/Errors/ExpectedExpressions.HC)";
    tests[0].FailMessage    = "Failed to recognise broken file (Tests/Errors/ExpectedExpressions.HC)";
    tests[0].Callback       = ParseInvalid;
    tests[0].ProgramData    = &l;
    tests[0].ExpectedResult = HC_False;
    tests[0].Assertion      = HC_True;

    HC_TestRuntineInfo ri;
    HC_TestRunTest(tests, sizeof(tests) / sizeof(HC_TestCreateInfo), &ri);
    
    HC_LexerDestroy(&l);
    return HC_True;
}
