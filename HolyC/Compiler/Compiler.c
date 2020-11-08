#include <Core-Backend/SDK.h>

static HC_Lexer *Lexer;

static U8 HC_CompilerValidateFile(const I8 *file)
{
    U64 fileStrlen = strlen(file);
    if (fileStrlen <= 1)
    {
        printf("Argument %s is an invalid file\n", file);
        return HC_False;
    }
    I8 extension[2];
    memset(extension, 0, sizeof(extension));
    strncpy(extension, file + (fileStrlen - 2), 2);
    
    /* file extensions are important for the lexer */
    U8 sourceFile = (strcmp(extension, "HC") == 0);
    U8 headerFile = (strcmp(extension, "HH") == 0);
    if (!(headerFile || sourceFile))
    {
        printf("Invalid extension %s, valid HH or HC\n", extension);
        return HC_False;
    }

    return HC_True;
}

static U8 HC_CompilerParseArguments(const U32 argumentCount, const I8 **arguments, HC_LexerLoadStreamInfo *info)
{
    if (argumentCount <= 1)
    {
        printf("No arguments specified\n");
        return HC_False;
    }
    const I8 *file = arguments[1];
    if (!HC_CompilerValidateFile(file))
        return HC_False;

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

    printf("Successfully parsed stream\n");
    
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
