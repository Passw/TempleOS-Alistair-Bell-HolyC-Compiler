#include <HolyC-SDK/SDK.h>

static HC_Lexer *Lexer;

static U8 HC_CompilerParseArguments(const U32 argumentCount, const I8 **arguments, HC_LexerLoadStreamInfo *info)
{
    if (argumentCount <= 1)
    {
        printf("No arguments specified\n");
        return HC_False;
    }
    info->Input         = arguments[1];
    info->LexerFlags    = HC_LEXER_FLAGS_NONE;
    return HC_True;
}

int main(const U32 argumentCount, const I8 **arguments)
{
    Lexer = malloc(sizeof(HC_Lexer));
    
    LexerLoad:
    {
        HC_LexerLoadStreamInfo loadInfo;
        memset(&loadInfo, 0, sizeof(HC_LexerLoadStreamInfo));
    
        if (!HC_CompilerParseArguments(argumentCount, arguments, &loadInfo))
            goto End;
        HC_LexerLoadStream(Lexer, &loadInfo);
    }
    
    while (HC_LexerParse(Lexer));









    End:
    {
        HC_LexerDestroy(Lexer);
        free(Lexer);
    }
    return 1;
}
