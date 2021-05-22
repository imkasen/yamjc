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
  
  Node* root;

  extern int node_id;
  
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

%type <Node*> ClassDeclarations Declarations DeclarStates Identifier Return

%type <Goal*> Goal
%type <MainClass*> MainClass 
%type <ClassDeclaration*> ClassDeclaration ClassExtendsDeclaration 
%type <VarDeclaration*> VarDeclaration
%type <MethodDeclaration*> MethodDeclaration
%type <FormalParameterList*> FormalParameterList
%type <Type*> Type
%type <Statement*> Statements Statement ElseStatement
%type <Expression*> Expression ExpressionList PrimaryExpression

%%

Goal : MainClass              { $$ = new Goal("Goal", ""); $$->children.push_back($1); root = $$; }
     | Goal ClassDeclarations { $$ = $1; $$->children.push_back($2); root = $$; }
     | END                    { $$ = new Goal("Goal", "EOF"); root = $$; }
     ;

MainClass : CLASS Identifier LBRACE PUBLIC STATIC VOID MAIN LPARENTHESE STRING LBRACKET RBRACKET Identifier RPARENTHESE LBRACE RBRACE RBRACE
              { $$ = new MainClass("MainClass", ""); $$->children.push_back($2); $$->children.push_back($12); }
          | CLASS Identifier LBRACE PUBLIC STATIC VOID MAIN LPARENTHESE STRING LBRACKET RBRACKET Identifier RPARENTHESE LBRACE DeclarStates RBRACE RBRACE 
              { $$ = new MainClass("MainClass", ""); $$->children.push_back($2); $$->children.push_back($12); $$->children.push_back($15); }
          ;

ClassDeclarations : ClassDeclaration        { $$ = $1; }
                  | ClassExtendsDeclaration { $$ = $1; }
                  ;

ClassDeclaration : CLASS Identifier LBRACE RBRACE              { $$ = new ClassDeclaration("ClassDeclaration", ""); $$->children.push_back($2); }
                 | CLASS Identifier LBRACE Declarations RBRACE { $$ = new ClassDeclaration("ClassDeclaration", ""); $$->children.push_back($2); $$->children.push_back($4); }
                 ;

ClassExtendsDeclaration : CLASS Identifier EXTENDS Identifier LBRACE RBRACE              { $$ = new ClassDeclaration("ClassDeclaration", ""); $$->children.push_back($2); $$->children.push_back($4); }
                        | CLASS Identifier EXTENDS Identifier LBRACE Declarations RBRACE { $$ = new ClassDeclaration("ClassDeclaration", ""); $$->children.push_back($2); $$->children.push_back($4); $$->children.push_back($6); }
                        ;

Declarations : VarDeclaration                 { $$ = new Node("Declarations", ""); $$->children.push_back($1); }
             | MethodDeclaration              { $$ = new Node("Declarations", ""); $$->children.push_back($1); }
             | Declarations VarDeclaration    { $$ = $1; $$->children.push_back($2); }
             | Declarations MethodDeclaration { $$ = $1; $$->children.push_back($2); }
             ;

VarDeclaration : Type Identifier SEMI { $$ = new VarDeclaration("VarDeclaration", ""); $$->children.push_back($1); $$->children.push_back($2); }
               ;

MethodDeclaration : PUBLIC Type Identifier LPARENTHESE RPARENTHESE LBRACE Return SEMI RBRACE 
                    { $$ = new MethodDeclaration("MethodDeclaration", ""); $$->children.push_back($2); $$->children.push_back($3); $$->children.push_back($7); }
                  | PUBLIC Type Identifier LPARENTHESE FormalParameterList RPARENTHESE LBRACE Return SEMI RBRACE
                    { $$ = new MethodDeclaration("MethodDeclaration", ""); $$->children.push_back($2); $$->children.push_back($3); $$->children.push_back($5); $$->children.push_back($8); }
                  | PUBLIC Type Identifier LPARENTHESE RPARENTHESE LBRACE DeclarStates Return SEMI RBRACE
                    { $$ = new MethodDeclaration("MethodDeclaration", ""); $$->children.push_back($2); $$->children.push_back($3); $$->children.push_back($7); $$->children.push_back($8); }
                  | PUBLIC Type Identifier LPARENTHESE FormalParameterList RPARENTHESE LBRACE DeclarStates Return SEMI RBRACE
                    { $$ = new MethodDeclaration("MethodDeclaration", ""); $$->children.push_back($2); $$->children.push_back($3); $$->children.push_back($5); $$->children.push_back($8); $$->children.push_back($9); }
                  ;

Return : RETURN Expression { $$ = new Node("Return", ""); $$->children.push_back($2); }
       ;

DeclarStates : VarDeclaration              { $$ = new Node("DeclarStates", ""); $$->children.push_back($1); }
             | Statement                   { $$ = new Node("DeclarStates", ""); $$->children.push_back($1); }
             | DeclarStates VarDeclaration { $$ = $1; $$->children.push_back($2); }
             | DeclarStates Statement      { $$ = $1; $$->children.push_back($2); }
             ;

FormalParameterList : Type Identifier                           { $$ = new FormalParameterList("FormalParameterList", ""); $$->children.push_back($1); $$->children.push_back($2); }
                    | FormalParameterList COMMA Type Identifier { $$ = $1; $$->children.push_back($3); $$->children.push_back($4); }
                    ;

Type : INT LBRACKET RBRACKET { $$ = new Type("Type", $1+$2+$3); }
     | BOOLEAN               { $$ = new Type("Type", $1); }
     | INT                   { $$ = new Type("Type", $1); }
     | Identifier            { $$ = new Type("Type", ""); $$->children.push_back($1); }
     ;

Statements : Statement            { $$ = new Statement("Statements", ""); $$->children.push_back($1); }
           | Statements Statement { $$ = $1; $$->children.push_back($2); }
           ;

Statement : LBRACE RBRACE                                                  { $$ = new Statement("Statement", "EMPTY"); }
          | LBRACE Statements RBRACE                                       { $$ = new Statement("Statement", ""); $$->children.push_back($2); }
          | Identifier ASSIGN Expression SEMI                              { $$ = new Statement("Statement", "="); $$->children.push_back($1); $$->children.push_back($3); }
          | Identifier LBRACKET Expression RBRACKET ASSIGN Expression SEMI { $$ = new Statement("Statement", "="); $$->children.push_back($1); $$->children.push_back($3); $$->children.push_back($6); }
          | IF LPARENTHESE Expression RPARENTHESE Statement ElseStatement  { $$ = new Statement("Statement", "IF"); $$->children.push_back($3); $$->children.push_back($5); $$->children.push_back($6); }
          | WHILE LPARENTHESE Expression RPARENTHESE Statement             { $$ = new Statement("Statement", "WHILE"); $$->children.push_back($3); $$->children.push_back($5); }
          | SOPRINTLN LPARENTHESE Expression RPARENTHESE SEMI              { $$ = new Statement("Statement", "S.O.PRINTLN"); $$->children.push_back($3); }
          ;

ElseStatement : ELSE Statement { $$ = new Statement("Statement", "ELSE"); $$->children.push_back($2); }
              ;

Expression : PrimaryExpression                                                { $$ = new Expression("Expression", ""); $$->children.push_back($1); }
           | Expression AND Expression                                        { $$ = new Expression("Expression", $2); $$->children.push_back($1); $$->children.push_back($3); }
           | Expression OR Expression                                         { $$ = new Expression("Expression", $2); $$->children.push_back($1); $$->children.push_back($3); }
           | Expression LT Expression                                         { $$ = new Expression("Expression", $2); $$->children.push_back($1); $$->children.push_back($3); }
           | Expression GT Expression                                         { $$ = new Expression("Expression", $2); $$->children.push_back($1); $$->children.push_back($3); }
           | Expression ADD Expression                                        { $$ = new Expression("Expression", $2); $$->children.push_back($1); $$->children.push_back($3); }
           | Expression SUB Expression                                        { $$ = new Expression("Expression", $2); $$->children.push_back($1); $$->children.push_back($3); }
           | Expression MUL Expression                                        { $$ = new Expression("Expression", $2); $$->children.push_back($1); $$->children.push_back($3); }
           | Expression DIV Expression                                        { $$ = new Expression("Expression", $2); $$->children.push_back($1); $$->children.push_back($3); }
           | Expression LBRACKET Expression RBRACKET                          { $$ = $1; $$->children.push_back($3); }
           | Expression DOT LENGTH                                            { $$ = new Expression("Expression", $3); $$->children.push_back($1); }
           | Expression DOT Identifier LPARENTHESE RPARENTHESE                { $$ = $1; $$->children.push_back($3); }
           | Expression DOT Identifier LPARENTHESE ExpressionList RPARENTHESE { $$ = $1; $$->children.push_back($3); $$->children.push_back($5); }
           ;

ExpressionList : Expression                      { $$ = new Expression("ExpressionList", ""); $$->children.push_back($1); }
               | ExpressionList COMMA Expression { $$ = $1; $$->children.push_back($3); }
               ;

PrimaryExpression : NEW INT LBRACKET Expression RBRACKET   { $$ = new Expression("PrimaryExpression", "NEW"); $$->children.push_back($4); }
                  | NEW Identifier LPARENTHESE RPARENTHESE { $$ = new Expression("PrimaryExpression", "NEW"); $$->children.push_back($2); }
                  | LPARENTHESE Expression RPARENTHESE     { $$ = new Expression("PrimaryExpression", ""); $$->children.push_back($2); } 
                  | Identifier                             { $$ = new Expression("PrimaryExpression", ""); $$->children.push_back($1); }
                  | NOT Expression                         { $$ = new Expression("PrimaryExpression", $1); $$->children.push_back($2); }
                  | NUM                                    { $$ = new Expression("Number", $1); }
                  | TRUE                                   { $$ = new Expression("Boolean", $1); }
                  | FALSE                                  { $$ = new Expression("Boolean", $1); }
                  | THIS                                   { $$ = new Expression("This", ""); }
                  ;

Identifier : IDENTIFIER { $$ = new Node("Identifier", $1); }
           ;
%%