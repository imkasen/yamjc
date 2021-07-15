%skeleton "lalr1.cc" 
%language "c++"
%defines
%define parse.error verbose
%define api.value.type variant
%define api.token.constructor

%code requires{
  #include "ast/nodes.h"
}

%code provides {
  extern FILE *yyin;
}

%code{
  #include "main.h"
  
  Node root;
}

%token <std::string> CLASS PUBLIC STATIC VOID MAIN STRING EXTENDS LENGTH NEW THIS RETURN
%token <std::string> IF ELSE WHILE
%token <std::string> SOPRINTLN
%token <std::string> INT BOOLEAN
%token <std::string> AND OR NOT
%token <std::string> TRUE FALSE
%token <std::string> LT GT
%token <std::string> ADD SUB MUL DIV
%token <std::string> LPARENTHESE RPARENTHESE LBRACKET RBRACKET LBRACE RBRACE
%token <std::string> SEMI COMMA ASSIGN DOT
%token <std::string> NUM IDENTIFIER

%token END 0 "end of file"

%right ASSIGN
%left DOT
%left AND OR LT GT
%left ADD SUB
%left MUL DIV
%right NOT
%left LBRACKET LBRACE LPARENTHESE

%start Goal

%type <Node> ClassDeclarations

%type <Goal> Goal
%type <MainClass> MainClass
%type <MethodBody> MethodBody
%type <ClassDeclaration> ClassDeclaration ClassExtendsDeclaration
%type <Declarations> Declarations
%type <VarDeclaration> VarDeclaration
%type <MethodDeclaration> MethodDeclaration
%type <FormalParameterList> FormalParameterList
%type <Type> Type
%type <Statement> Statements Statement ElseStatement
%type <Expression> Expression ExpressionList PrimaryExpression
%type <Return> Return
%type <Identifier> Identifier

%%

Goal : MainClass              { $$ = Goal("Goal", ""); $$.children.push_back($1); root = $$; }
     | Goal ClassDeclarations { $$ = $1; $$.children.push_back($2); root = $$; }
     | END                    { $$ = Goal("Goal", "EOF"); root = $$; }
     ;

MainClass : CLASS Identifier LBRACE PUBLIC STATIC VOID MAIN LPARENTHESE STRING LBRACKET RBRACKET Identifier RPARENTHESE LBRACE RBRACE RBRACE
              { $$ = MainClass("MainClass", ""); $$.children.push_back($2); $$.children.push_back($12); }
          | CLASS Identifier LBRACE PUBLIC STATIC VOID MAIN LPARENTHESE STRING LBRACKET RBRACKET Identifier RPARENTHESE LBRACE MethodBody RBRACE RBRACE
              { $$ = MainClass("MainClass", ""); $$.children.push_back($2); $$.children.push_back($12); $$.children.push_back($15); }
          ;

ClassDeclarations : ClassDeclaration        { $$ = $1; }
                  | ClassExtendsDeclaration { $$ = $1; }
                  ;

ClassDeclaration : CLASS Identifier LBRACE RBRACE              { $$ = ClassDeclaration("ClassDeclaration", ""); $$.children.push_back($2); }
                 | CLASS Identifier LBRACE Declarations RBRACE { $$ = ClassDeclaration("ClassDeclaration", ""); $$.children.push_back($2); $$.children.push_back($4); }
                 ;

ClassExtendsDeclaration : CLASS Identifier EXTENDS Identifier LBRACE RBRACE              { $$ = ClassDeclaration("ClassDeclaration", ""); $$.children.push_back($2); $$.children.push_back($4); }
                        | CLASS Identifier EXTENDS Identifier LBRACE Declarations RBRACE { $$ = ClassDeclaration("ClassDeclaration", ""); $$.children.push_back($2); $$.children.push_back($4); $$.children.push_back($6); }
                        ;

Declarations : VarDeclaration                 { $$ = Declarations("Declarations", ""); $$.children.push_back($1); }
             | MethodDeclaration              { $$ = Declarations("Declarations", ""); $$.children.push_back($1); }
             | Declarations VarDeclaration    { $$ = $1; $$.children.push_back($2); }
             | Declarations MethodDeclaration { $$ = $1; $$.children.push_back($2); }
             ;

VarDeclaration : Type Identifier SEMI { $$ = VarDeclaration("VarDeclaration", ""); $$.children.push_back($1); $$.children.push_back($2); }
               ;

MethodDeclaration : PUBLIC Type Identifier LPARENTHESE RPARENTHESE LBRACE Return SEMI RBRACE
                    { $$ = MethodDeclaration("MethodDeclaration", ""); $$.children.push_back($2); $$.children.push_back($3); $$.children.push_back($7); }
                  | PUBLIC Type Identifier LPARENTHESE FormalParameterList RPARENTHESE LBRACE Return SEMI RBRACE
                    { $$ = MethodDeclaration("MethodDeclaration", ""); $$.children.push_back($2); $$.children.push_back($3); $$.children.push_back($5); $$.children.push_back($8); }
                  | PUBLIC Type Identifier LPARENTHESE RPARENTHESE LBRACE MethodBody SEMI RBRACE
                    { $$ = MethodDeclaration("MethodDeclaration", ""); $$.children.push_back($2); $$.children.push_back($3); $$.children.push_back($7); }
                  | PUBLIC Type Identifier LPARENTHESE FormalParameterList RPARENTHESE LBRACE MethodBody SEMI RBRACE
                    { $$ = MethodDeclaration("MethodDeclaration", ""); $$.children.push_back($2); $$.children.push_back($3); $$.children.push_back($5); $$.children.push_back($8); }
                  ;

MethodBody : VarDeclaration            { $$ = MethodBody("MethodBody", ""); $$.children.push_back($1); }
           | Statement                 { $$ = MethodBody("MethodBody", ""); $$.children.push_back($1); }
           | MethodBody VarDeclaration { $$ = $1; $$.children.push_back($2); }
           | MethodBody Statement      { $$ = $1; $$.children.push_back($2); }
           | MethodBody Return         { $$ = $1; $$.children.push_back($2); }
           ;

Return : RETURN Expression { $$ = Return("Return", ""); $$.children.push_back($2); }
       ;

FormalParameterList : Type Identifier                           { $$ = FormalParameterList("FormalParameterList", ""); $$.children.push_back($1); $$.children.push_back($2); }
                    | FormalParameterList COMMA Type Identifier { $$ = $1; $$.children.push_back($3); $$.children.push_back($4); }
                    ;

Type : INT LBRACKET RBRACKET { $$ = Type("Type", $1+$2+$3); }
     | BOOLEAN               { $$ = Type("Type", $1); }
     | INT                   { $$ = Type("Type", $1); }
     | Identifier            { $$ = Type("Type", ""); $$.children.push_back($1); }
     ;

Statements : Statement            { $$ = Statement("Statements", ""); $$.children.push_back($1); }
           | Statements Statement { $$ = $1; $$.children.push_back($2); }
           ;

Statement : LBRACE RBRACE                                                  { $$ = Statement("Statement", "EMPTY"); }
          | LBRACE Statements RBRACE                                       { $$ = Statement("Statement", ""); $$.children.push_back($2); }
          | Identifier ASSIGN Expression SEMI                              { $$ = Statement("Statement", "="); $$.children.push_back($1); $$.children.push_back($3); }
          | Identifier LBRACKET Expression RBRACKET ASSIGN Expression SEMI { $$ = Statement("Statement", "="); $$.children.push_back($1); $$.children.push_back($3); $$.children.push_back($6); }
          | IF LPARENTHESE Expression RPARENTHESE Statement ElseStatement  { $$ = Statement("Statement", "IF"); $$.children.push_back($3); $$.children.push_back($5); $$.children.push_back($6); }
          | WHILE LPARENTHESE Expression RPARENTHESE Statement             { $$ = Statement("Statement", "WHILE"); $$.children.push_back($3); $$.children.push_back($5); }
          | SOPRINTLN LPARENTHESE Expression RPARENTHESE SEMI              { $$ = Statement("Statement", "S.O.PRINTLN"); $$.children.push_back($3); }
          ;

ElseStatement : ELSE Statement { $$ = Statement("Statement", "ELSE"); $$.children.push_back($2); }
              ;

Expression : PrimaryExpression                                                { $$ = Expression("Expression", ""); $$.children.push_back($1); }
           | Expression AND Expression                                        { $$ = Expression("Expression", $2); $$.children.push_back($1); $$.children.push_back($3); }
           | Expression OR Expression                                         { $$ = Expression("Expression", $2); $$.children.push_back($1); $$.children.push_back($3); }
           | Expression LT Expression                                         { $$ = Expression("Expression", $2); $$.children.push_back($1); $$.children.push_back($3); }
           | Expression GT Expression                                         { $$ = Expression("Expression", $2); $$.children.push_back($1); $$.children.push_back($3); }
           | Expression ADD Expression                                        { $$ = Expression("Expression", $2); $$.children.push_back($1); $$.children.push_back($3); }
           | Expression SUB Expression                                        { $$ = Expression("Expression", $2); $$.children.push_back($1); $$.children.push_back($3); }
           | Expression MUL Expression                                        { $$ = Expression("Expression", $2); $$.children.push_back($1); $$.children.push_back($3); }
           | Expression DIV Expression                                        { $$ = Expression("Expression", $2); $$.children.push_back($1); $$.children.push_back($3); }
           | Expression LBRACKET Expression RBRACKET                          { $$ = $1; $$.children.push_back($3); }
           | Expression DOT LENGTH                                            { $$ = Expression("Expression", $3); $$.children.push_back($1); }
           | Expression DOT Identifier LPARENTHESE RPARENTHESE                { $$ = $1; $$.children.push_back($3); }
           | Expression DOT Identifier LPARENTHESE ExpressionList RPARENTHESE { $$ = $1; $$.children.push_back($3); $$.children.push_back($5); }
           ;

ExpressionList : Expression                      { $$ = Expression("ExpressionList", ""); $$.children.push_back($1); }
               | ExpressionList COMMA Expression { $$ = $1; $$.children.push_back($3); }
               ;

PrimaryExpression : NEW INT LBRACKET Expression RBRACKET   { $$ = Expression("PrimaryExpression", "NEW"); $$.children.push_back($4); }
                  | NEW Identifier LPARENTHESE RPARENTHESE { $$ = Expression("PrimaryExpression", "NEW"); $$.children.push_back($2); }
                  | LPARENTHESE Expression RPARENTHESE     { $$ = Expression("PrimaryExpression", ""); $$.children.push_back($2); }
                  | Identifier                             { $$ = Expression("PrimaryExpression", ""); $$.children.push_back($1); }
                  | NOT Expression                         { $$ = Expression("PrimaryExpression", $1); $$.children.push_back($2); }
                  | NUM                                    { $$ = Expression("Number", $1); }
                  | TRUE                                   { $$ = Expression("Boolean", $1); }
                  | FALSE                                  { $$ = Expression("Boolean", $1); }
                  | THIS                                   { $$ = Expression("This", ""); }
                  ;

Identifier : IDENTIFIER { $$ = Identifier("Identifier", $1); }
           ;
%%