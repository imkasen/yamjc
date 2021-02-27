%skeleton "lalr1.cc" 
%language "c++"
%defines
%define parse.error verbose
%define api.value.type variant
%define api.token.constructor

%code requires{
  #include "node.h"
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

%type <Node *> Goal MainClass 
%type <Node *> ClassDeclarations ClassDeclaration ClassExtendsDeclaration Declarations VarDeclaration MethodDeclaration
%type <Node *> Statements Statement
%type <Node *> Expression ExpressionList PrimaryExpression
%type <Node *> DeclarStates FormalParameterList Type Identifier

%%

Goal : MainClass              { $$ = new Node("Goal", ""); $$->children.push_back($1); root = $$; }
     | Goal ClassDeclarations { $$ = $1; $$->children.push_back($2); root = $$; }
     | END                    { $$ = new Node("Goal", "EOF"); root = $$; }
     ;

MainClass : CLASS Identifier LBRACE PUBLIC STATIC VOID MAIN LPARENTHESE STRING LBRACKET RBRACKET Identifier RPARENTHESE LBRACE RBRACE RBRACE
              { $$ = new Node("MainClass", ""); $$->children.push_back($2); $$->children.push_back($12); }
          | CLASS Identifier LBRACE PUBLIC STATIC VOID MAIN LPARENTHESE STRING LBRACKET RBRACKET Identifier RPARENTHESE LBRACE DeclarStates RBRACE RBRACE 
              { $$ = new Node("MainClass", ""); $$->children.push_back($2); $$->children.push_back($12); $$->children.push_back($15); }
          ;

ClassDeclarations : ClassDeclaration        { $$ = $1; }
                  | ClassExtendsDeclaration { $$ = $1; }
                  ;

ClassDeclaration : CLASS Identifier LBRACE RBRACE              { $$ = new Node("ClassDeclaration", ""); $$->children.push_back($2); }
                 | CLASS Identifier LBRACE Declarations RBRACE { $$ = new Node("ClassDeclaration", ""); $$->children.push_back($2); $$->children.push_back($4); }
                 ;

ClassExtendsDeclaration : CLASS Identifier EXTENDS Identifier LBRACE RBRACE              { $$ = new Node("ClassDeclaration", ""); $$->children.push_back($2); $$->children.push_back($4); }
                        | CLASS Identifier EXTENDS Identifier LBRACE Declarations RBRACE { $$ = new Node("ClassDeclaration", ""); $$->children.push_back($2); $$->children.push_back($4); $$->children.push_back($6); }
                        ;

Declarations : VarDeclaration                 { $$ = new Node("Declarations", ""); $$->children.push_back($1); }
             | MethodDeclaration              { $$ = new Node("Declarations", ""); $$->children.push_back($1); }
             | Declarations VarDeclaration    { $$ = $1; $$->children.push_back($2); }
             | Declarations MethodDeclaration { $$ = $1; $$->children.push_back($2); }
             ;

VarDeclaration : Type Identifier SEMI { $$ = new Node("VarDeclaration", ""); $$->children.push_back($1); $$->children.push_back($2); }
               ;

MethodDeclaration : PUBLIC Type Identifier LPARENTHESE RPARENTHESE LBRACE RETURN Expression SEMI RBRACE 
                    { $$ = new Node("MethodDeclaration", ""); $$->children.push_back($2); $$->children.push_back($3); $$->children.push_back($8); }
                  | PUBLIC Type Identifier LPARENTHESE FormalParameterList RPARENTHESE LBRACE RETURN Expression SEMI RBRACE
                    { $$ = new Node("MethodDeclaration", ""); $$->children.push_back($2); $$->children.push_back($3); $$->children.push_back($5); $$->children.push_back($9); }
                  | PUBLIC Type Identifier LPARENTHESE RPARENTHESE LBRACE DeclarStates RETURN Expression SEMI RBRACE
                    { $$ = new Node("MethodDeclaration", ""); $$->children.push_back($2); $$->children.push_back($3); $$->children.push_back($7); $$->children.push_back($9); }
                  | PUBLIC Type Identifier LPARENTHESE FormalParameterList RPARENTHESE LBRACE DeclarStates RETURN Expression SEMI RBRACE
                    { $$ = new Node("MethodDeclaration", ""); $$->children.push_back($2); $$->children.push_back($3); $$->children.push_back($5); $$->children.push_back($8); $$->children.push_back($10); }
                  ;

DeclarStates : VarDeclaration              { $$ = new Node("DeclarStates", ""); $$->children.push_back($1); }
             | Statement                   { $$ = new Node("DeclarStates", ""); $$->children.push_back($1); }
             | DeclarStates VarDeclaration { $$ = $1; $$->children.push_back($2); }
             | DeclarStates Statement      { $$ = $1; $$->children.push_back($2); }
             ;

FormalParameterList : Type Identifier                           { $$ = new Node("FormalParameterList", ""); $$->children.push_back($1); $$->children.push_back($2); }
                    | FormalParameterList COMMA Type Identifier { $$ = $1; $$->children.push_back($3); $$->children.push_back($4); }
                    ;

Type : INT LBRACKET RBRACKET { $$ = new Node("Type", $1+$2+$3); }
     | BOOLEAN               { $$ = new Node("Type", $1); }
     | INT                   { $$ = new Node("Type", $1); }
     | Identifier            { $$ = new Node("Type", ""); $$->children.push_back($1); }
     ;

Statements : Statement            { $$ = new Node("Statements", ""); $$->children.push_back($1); }
           | Statements Statement { $$ = $1; $$->children.push_back($2); }
           ;

Statement : LBRACE RBRACE                                                  { $$ = new Node("Statement", "Empty"); }
          | LBRACE Statements RBRACE                                       { $$ = new Node("Statement", ""); $$->children.push_back($2); }
          | Identifier ASSIGN Expression SEMI                              { $$ = new Node("Statement", ""); $$->children.push_back($1); $$->children.push_back($3); }
          | Identifier LBRACKET Expression RBRACKET ASSIGN Expression SEMI { $$ = new Node("Statement", ""); $$->children.push_back($1); $$->children.push_back($3); $$->children.push_back($6); }
          | IF LPARENTHESE Expression RPARENTHESE Statement ELSE Statement { $$ = new Node("Statement", ""); $$->children.push_back($3); $$->children.push_back($5); $$->children.push_back($7); }
          | WHILE LPARENTHESE Expression RPARENTHESE Statement             { $$ = new Node("Statement", ""); $$->children.push_back($3); $$->children.push_back($5); }
          | SOPRINTLN LPARENTHESE Expression RPARENTHESE SEMI              { $$ = new Node("Statement", ""); $$->children.push_back($3); }
          ;

Expression : PrimaryExpression                                                { $$ = new Node("Expression", ""); $$->children.push_back($1); } 
           | Expression AND PrimaryExpression                                 { $$ = $1; $$->children.push_back($3); }
           | Expression OR PrimaryExpression                                  { $$ = $1; $$->children.push_back($3); }
           | Expression LT PrimaryExpression                                  { $$ = $1; $$->children.push_back($3); }
           | Expression GT PrimaryExpression                                  { $$ = $1; $$->children.push_back($3); }
           | Expression ADD PrimaryExpression                                 { $$ = $1; $$->children.push_back($3); }
           | Expression SUB PrimaryExpression                                 { $$ = $1; $$->children.push_back($3); }
           | Expression MUL PrimaryExpression                                 { $$ = $1; $$->children.push_back($3); }
           | Expression DIV PrimaryExpression                                 { $$ = $1; $$->children.push_back($3); }
           | Expression LBRACKET PrimaryExpression RBRACKET                   { $$ = $1; $$->children.push_back($3); }
           | Expression DOT LENGTH                                            { $$ = $1; }
           | Expression DOT Identifier LPARENTHESE RPARENTHESE                { $$ = $1; $$->children.push_back($3); }
           | Expression DOT Identifier LPARENTHESE ExpressionList RPARENTHESE { $$ = $1; $$->children.push_back($3); $$->children.push_back($5); }
           ;

ExpressionList : Expression                      { $$ = new Node("ExpressionList", ""); $$->children.push_back($1); }
               | ExpressionList COMMA Expression { $$ = $1; $$->children.push_back($3); }
               ;

PrimaryExpression : NEW INT LBRACKET Expression RBRACKET   { $$ = new Node("PrimaryExpression", ""); $$->children.push_back($4); }
                  | NEW Identifier LPARENTHESE RPARENTHESE { $$ = new Node("PrimaryExpression", ""); $$->children.push_back($2); }
                  | LPARENTHESE Expression RPARENTHESE     { $$ = new Node("PrimaryExpression", ""); $$->children.push_back($2); } 
                  | Identifier                             { $$ = new Node("PrimaryExpression", ""); $$->children.push_back($1); }
                  | NOT Expression                         { $$ = new Node("PrimaryExpression", $1); $$->children.push_back($2); }
                  | NUM                                    { $$ = new Node("Number", $1); }
                  | TRUE                                   { $$ = new Node("Boolean", $1); }
                  | FALSE                                  { $$ = new Node("Boolean", $1); }
                  | THIS                                   { $$ = new Node("This", $1); }
                  ;

Identifier : IDENTIFIER { $$ = new Node("Identifier", $1); }
           ;
%%