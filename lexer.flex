%top{
    #include "main.h"

    #define YYSTYPE int
}

%option noyywrap

%x COMMENT

%%

"class"                    { cout << "Token class:              " << yytext << endl; }
"public"                   { cout << "Token public:             " << yytext << endl; }
"static"                   { cout << "Token static:             " << yytext << endl; }
"void"                     { cout << "Token void:               " << yytext << endl; }
"main"                     { cout << "Token main:               " << yytext << endl; }
"String"                   { cout << "Token String:             " << yytext << endl; }
"extends"                  { cout << "Token extends:            " << yytext << endl; }
"length"                   { cout << "Token length:             " << yytext << endl; }
"new"                      { cout << "Token new:                " << yytext << endl; }
"this"                     { cout << "Token this:               " << yytext << endl; }
"return"                   { cout << "Token return:             " << yytext << endl; }

"if"                       { cout << "Token if:                 " << yytext << endl; }
"else"                     { cout << "Token else:               " << yytext << endl; }
"while"                    { cout << "Token while:              " << yytext << endl; }

"System.out.println"       { cout << "Token System.out.println: " << yytext << endl; }

"int"                      { cout << "Token int:                " << yytext << endl; }
"boolean"                  { cout << "Token boolean:            " << yytext << endl; }

"&&"                       { cout << "Token and:                " << yytext << endl; }
"||"                       { cout << "Token or:                 " << yytext << endl; }
"!"                        { cout << "Token negation:           " << yytext << endl; }

"true"                     { cout << "Token true:               " << yytext << endl; }
"false"                    { cout << "Token false:              " << yytext << endl; }

"<"                        { cout << "Token lessthan:           " << yytext << endl; }
">"                        { cout << "Token greatthan:          " << yytext << endl; }

"+"                        { cout << "Token add:                " << yytext << endl; }
"-"                        { cout << "Token sub:                " << yytext << endl; }
"*"                        { cout << "Token mul:                " << yytext << endl; }
"/"                        { cout << "Token div:                " << yytext << endl; }

"("                        { cout << "Token left parenthese:    " << yytext << endl; }
")"                        { cout << "Token right parenthese:   " << yytext << endl; }
"["                        { cout << "Token left bracket:       " << yytext << endl; }
"]"                        { cout << "Token right bracket:      " << yytext << endl; }
"{"                        { cout << "Token left brace:         " << yytext << endl; }
"}"                        { cout << "Token right brace:        " << yytext << endl; }

[ \t]                      { /* space */ }
\n                         { /* new line */ }
";"                        { cout << "Token semicolon:          " << yytext << endl; }
","                        { cout << "Token comma:              " << yytext << endl; }
"="                        { cout << "Token assign:             " << yytext << endl; }
"."                        { cout << "Token dot:                " << yytext << endl; }

"//"                       { BEGIN(COMMENT); }
<COMMENT>.*                { /* comment */ }
<COMMENT>\n                { BEGIN(0); }

[0-9]+                     { cout << "INTEGER_LITERAL:          " << yytext << endl; }
[_a-zA-Z\$][_a-zA-Z0-9\$]* { cout << "IDENTIFIER:               " << yytext << endl; }

<<EOF>>                    { yyterminate(); }

%%