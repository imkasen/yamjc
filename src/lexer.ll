%top{
    #include "ast/node.h"
    #include "main.h"
}

%option noyywrap nounput batch noinput stack

%%

"class"                    { return yy::parser::make_CLASS(yytext); }
"public"                   { return yy::parser::make_PUBLIC(yytext); }
"static"                   { return yy::parser::make_STATIC(yytext); }
"void"                     { return yy::parser::make_VOID(yytext); }
"main"                     { return yy::parser::make_MAIN(yytext); }
"String"                   { return yy::parser::make_STRING(yytext); }
"extends"                  { return yy::parser::make_EXTENDS(yytext); }
"length"                   { return yy::parser::make_LENGTH(yytext); }
"new"                      { return yy::parser::make_NEW(yytext); }
"this"                     { return yy::parser::make_THIS(yytext); }
"return"                   { return yy::parser::make_RETURN(yytext); }

"if"                       { return yy::parser::make_IF(yytext); }
"else"                     { return yy::parser::make_ELSE(yytext); }
"while"                    { return yy::parser::make_WHILE(yytext); }

"System.out.println"       { return yy::parser::make_SOPRINTLN(yytext); }

"int"                      { return yy::parser::make_INT(yytext); }
"boolean"                  { return yy::parser::make_BOOLEAN(yytext); }

"&&"                       { return yy::parser::make_AND(yytext); }
"||"                       { return yy::parser::make_OR(yytext); }
"!"                        { return yy::parser::make_NOT(yytext); }
"=="                       { return yy::parser::make_EQUAL(yytext); }
"!="                       { return yy::parser::make_NOTEQUAL(yytext); }

"true"                     { return yy::parser::make_TRUE(yytext); }
"false"                    { return yy::parser::make_FALSE(yytext); }

"<"                        { return yy::parser::make_LT(yytext); }
"<="                       { return yy::parser::make_LET(yytext); }
">"                        { return yy::parser::make_GT(yytext); }
">="                       { return yy::parser::make_GET(yytext); }

"+"                        { return yy::parser::make_ADD(yytext); }
"-"                        { return yy::parser::make_SUB(yytext); }
"*"                        { return yy::parser::make_MUL(yytext); }
"/"                        { return yy::parser::make_DIV(yytext); }

"("                        { return yy::parser::make_LPARENTHESE(yytext); }
")"                        { return yy::parser::make_RPARENTHESE(yytext); }
"["                        { return yy::parser::make_LBRACKET(yytext); }
"]"                        { return yy::parser::make_RBRACKET(yytext); }
"{"                        { return yy::parser::make_LBRACE(yytext); }
"}"                        { return yy::parser::make_RBRACE(yytext); }

[ \t\n]+                   { /* space, new line */ }
";"                        { return yy::parser::make_SEMI(yytext); }
","                        { return yy::parser::make_COMMA(yytext); }
"="                        { return yy::parser::make_ASSIGN(yytext); }
"."                        { return yy::parser::make_DOT(yytext); }

"//".*                     { /* comment */ }
"/*"(.|\n)*"*/"            { /* comment */ }

[0-9]+                     { return yy::parser::make_NUM(yytext); }
[_a-zA-Z\$][_a-zA-Z0-9\$]* { return yy::parser::make_IDENTIFIER(yytext); }

<<EOF>>                    { return yy::parser::make_END(); }

%%