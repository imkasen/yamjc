#include "main.h"

extern int yylex();
extern FILE *yyin;

void yyerror(const string &err)
{
    std::cerr << err << endl;
}

int main(int argc, char* argv[])
{
    // read file from cmd
    if (argc > 1)
    {
        FILE *file = std::fopen(argv[1], "r");
        if (file)
        {
            yyin = file;
        }
        else
        {
            yyin = stdin;
        }

        if (!yylex())
        {
            cout << "Lexer finish running" << endl;
        }
        
        std::fclose(file);
    }
    return 0;
}
