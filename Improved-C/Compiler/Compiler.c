#include <Improved-C-SDK/SDK.h>

static IC_Lexer *Lexer;

static U8 IC_CompilerParseArguments(const U32 argumentCount, const I8 **arguments, IC_LexerLoadStreamInfo *info)
{
    if (argumentCount <= 1)
    {
        printf("No arguments specified\n");
        return IC_False;
    }
    info->Input         = arguments[1];
    info->LexerFlags    = IC_LEXER_FLAGS_NONE;
    return IC_True;
}

int main(const U32 argumentCount, const I8 **arguments)
{
    Lexer = malloc(sizeof(IC_Lexer));
    
    LexerLoad:
    {
        IC_LexerLoadStreamInfo loadInfo;
        memset(&loadInfo, 0, sizeof(IC_LexerLoadStreamInfo));
    
        if (!IC_CompilerParseArguments(argumentCount, arguments, &loadInfo))
            goto End;
        IC_LexerLoadStream(Lexer, &loadInfo);
    }

    End:
    {
        IC_LexerDestroy(Lexer);
        free(Lexer);
    }
    return 1;
}
