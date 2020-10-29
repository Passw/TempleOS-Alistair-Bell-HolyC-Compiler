#include <Improved-C-SDK/SDK.h>

static IC_Lexer *Lexer;

int main(const U32 argumentCount, const I8 **arguments)
{
    Lexer = malloc(sizeof(IC_Lexer));
    
    const char *compiling;
    if (argumentCount <= 1)
    {
        printf("No file specified using Tests/Main.IC\n");
        compiling = "Tests/Main.IC";
    }
    else
    {
        compiling = arguments[1];
    }

    
    LexerCreate:
    {
        IC_LexerCreateInfo createInfo;
        memset(&createInfo, 0, sizeof(IC_LexerCreateInfo));
        
        
        IC_LexerCreate(Lexer, &createInfo);
    }
    

    LexerLoad:
    {
        IC_LexerLoadStreamInfo loadInfo;
        memset(&loadInfo, 0, sizeof(IC_LexerLoadStreamInfo));
        loadInfo.Input = compiling;

        IC_LexerLoadStream(Lexer, &loadInfo);
    }



    IC_LexerDestroy(Lexer);
    free(Lexer);
    return 1;
}