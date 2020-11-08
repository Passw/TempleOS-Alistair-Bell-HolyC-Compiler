#include <Core-Backend/SDK.h>

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

I32 main(const U32 argumentCount, const I8 **arguments)
{
    Lexer = malloc(sizeof(HC_Lexer));
    LexerLoad:
    {
        HC_LexerLoadStreamInfo loadInfo;
        memset(&loadInfo, 0, sizeof(HC_LexerLoadStreamInfo));
    
        if (!HC_CompilerParseArguments(argumentCount, arguments, &loadInfo))
            goto End;
        if (!HC_LexerLoadStream(Lexer, &loadInfo))
            goto End;
    }
    
    if (!HC_LexerParse(Lexer))
    {
        printf("Unable to parse %s\n", arguments[0]);
        goto End;
    }

    U64 i;
    for (i = 0; i < Lexer->CurrentFile->TokenCount; i++)
        printf("%s\n", Lexer->CurrentFile->Tokens[i].Source);



    End:
    {
        HC_LexerDestroy(Lexer);
        free(Lexer);
    }
    return 1;
}
