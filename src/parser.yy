%skeleton "lalr1.cc"
%require "3.2"
%language "c++"
%defines
%define parse.error verbose
%define api.value.type variant
%define api.token.constructor

%code requires {
  #include "ast/nodes.h"

  using std::string;
  using std::shared_ptr;
  using std::make_shared;
}

%code provides {
  extern FILE *yyin;
}

%code {
  #include "main.h"

  shared_ptr<Node> root;
}

%token <string> CLASS PUBLIC STATIC VOID MAIN STRING EXTENDS LENGTH NEW THIS RETURN
%token <string> IF ELSE WHILE
%token <string> SOPRINTLN
%token <string> INT BOOLEAN
%token <string> AND OR NOT EQUAL NOTEQUAL
%token <string> TRUE FALSE
%token <string> LT LET GT GET
%token <string> ADD SUB MUL DIV
%token <string> LPARENTHESE RPARENTHESE LBRACKET RBRACKET LBRACE RBRACE
%token <string> SEMI COMMA ASSIGN DOT
%token <string> NUM IDENTIFIER

%token END 0 "end of file"

%right ASSIGN
%left OR
%left AND
%left EQUAL NOTEQUAL
%left LT LET GT GET
%left ADD SUB
%left MUL DIV
%right NOT
%left LBRACKET LBRACE LPARENTHESE DOT

%start Goal

%type <shared_ptr<Goal>> Goal
%type <shared_ptr<MainClass>> MainClass
%type <shared_ptr<MethodBody>> MethodBody
%type <shared_ptr<Type>> Type
%type <shared_ptr<Return>> Return
%type <shared_ptr<Identifier>> Identifier

%type <shared_ptr<Node>> ClassDeclarations
%type <shared_ptr<ClassDeclaration>> ClassDeclaration
%type <shared_ptr<ClassExtendsDeclaration>> ClassExtendsDeclaration
%type <shared_ptr<Declarations>> Declarations
%type <shared_ptr<VarDeclaration>> VarDeclaration
%type <shared_ptr<MethodDeclaration>> MethodDeclaration

%type <shared_ptr<FormalParameterList>> FormalParameterList
%type <shared_ptr<FormalParameter>> FormalParameter

%type <shared_ptr<Expression>> Expression
%type <shared_ptr<ExpressionList>> ExpressionList
%type <shared_ptr<LogicExpression>> LogicExpression
%type <shared_ptr<CompareExpression>> CompareExpression
%type <shared_ptr<ArithExpression>> ArithExpression
%type <shared_ptr<ArraySearchExpression>> ArraySearchExpression
%type <shared_ptr<ArrayLengthExpression>> ArrayLengthExpression

%type <shared_ptr<PrimaryExpression>> PrimaryExpression
%type <shared_ptr<ArrayAllocExpression>> ArrayAllocExpression
%type <shared_ptr<AllocExpression>> AllocExpression
%type <shared_ptr<UnaryExpression>> UnaryExpression

%type <shared_ptr<Statement>> Statements Statement
%type <shared_ptr<AssignStatement>> AssignStatement
%type <shared_ptr<ArrayAssignStatement>> ArrayAssignStatement
%type <shared_ptr<IfStatement>> IfStatement
%type <shared_ptr<ElseStatement>> ElseStatement
%type <shared_ptr<WhileStatement>> WhileStatement
%type <shared_ptr<PrintStatement>> PrintStatement

%%

Goal : MainClass              { $$ = make_shared<Goal>("Goal", ""); $$->children.push_back($1); root = $$; }
     | Goal ClassDeclarations { $$ = $1; $$->children.push_back($2); root = $$; }
     | END                    { $$ = make_shared<Goal>("Goal", "EOF"); root = $$; }
     ;

MainClass : CLASS Identifier LBRACE PUBLIC STATIC VOID MAIN LPARENTHESE STRING LBRACKET RBRACKET Identifier RPARENTHESE LBRACE RBRACE RBRACE
              { $$ = make_shared<MainClass>("MainClass", ""); $$->children.push_back($2); $$->children.push_back($12); }
          | CLASS Identifier LBRACE PUBLIC STATIC VOID MAIN LPARENTHESE STRING LBRACKET RBRACKET Identifier RPARENTHESE LBRACE MethodBody RBRACE RBRACE
              { $$ = make_shared<MainClass>("MainClass", ""); $$->children.push_back($2); $$->children.push_back($12); $$->children.push_back($15); }
          ;

ClassDeclarations : ClassDeclaration        { $$ = $1; }
                  | ClassExtendsDeclaration { $$ = $1; }
                  ;

ClassDeclaration : CLASS Identifier LBRACE RBRACE              { $$ = make_shared<ClassDeclaration>("ClassDeclaration", ""); $$->children.push_back($2); }
                 | CLASS Identifier LBRACE Declarations RBRACE { $$ = make_shared<ClassDeclaration>("ClassDeclaration", ""); $$->children.push_back($2); $$->children.push_back($4); }
                 ;

ClassExtendsDeclaration : CLASS Identifier EXTENDS Identifier LBRACE RBRACE              { $$ = make_shared<ClassExtendsDeclaration>("ClassExtendsDeclaration", $3); $$->children.push_back($2); $$->children.push_back($4); }
                        | CLASS Identifier EXTENDS Identifier LBRACE Declarations RBRACE { $$ = make_shared<ClassExtendsDeclaration>("ClassExtendsDeclaration", $3); $$->children.push_back($2); $$->children.push_back($4); $$->children.push_back($6); }
                        ;

Declarations : VarDeclaration                 { $$ = make_shared<Declarations>("Declarations", ""); $$->children.push_back($1); }
             | MethodDeclaration              { $$ = make_shared<Declarations>("Declarations", ""); $$->children.push_back($1); }
             | Declarations VarDeclaration    { $$ = $1; $$->children.push_back($2); }
             | Declarations MethodDeclaration { $$ = $1; $$->children.push_back($2); }
             ;

VarDeclaration : Type Identifier SEMI { $$ = make_shared<VarDeclaration>("VarDeclaration", ""); $$->children.push_back($1); $$->children.push_back($2); }
               ;

MethodDeclaration : PUBLIC Type Identifier LPARENTHESE RPARENTHESE LBRACE Return SEMI RBRACE
                    { $$ = make_shared<MethodDeclaration>("MethodDeclaration", ""); $$->children.push_back($2); $$->children.push_back($3); $$->children.push_back($7); }
                  | PUBLIC Type Identifier LPARENTHESE FormalParameterList RPARENTHESE LBRACE Return SEMI RBRACE
                    { $$ = make_shared<MethodDeclaration>("MethodDeclaration", ""); $$->children.push_back($2); $$->children.push_back($3); $$->children.push_back($5); $$->children.push_back($8); }
                  | PUBLIC Type Identifier LPARENTHESE RPARENTHESE LBRACE MethodBody SEMI RBRACE
                    { $$ = make_shared<MethodDeclaration>("MethodDeclaration", ""); $$->children.push_back($2); $$->children.push_back($3); $$->children.push_back($7); }
                  | PUBLIC Type Identifier LPARENTHESE FormalParameterList RPARENTHESE LBRACE MethodBody SEMI RBRACE
                    { $$ = make_shared<MethodDeclaration>("MethodDeclaration", ""); $$->children.push_back($2); $$->children.push_back($3); $$->children.push_back($5); $$->children.push_back($8); }
                  ;

MethodBody : VarDeclaration            { $$ = make_shared<MethodBody>("MethodBody", ""); $$->children.push_back($1); }
           | Statement                 { $$ = make_shared<MethodBody>("MethodBody", ""); $$->children.push_back($1); }
           | MethodBody VarDeclaration { $$ = $1; $$->children.push_back($2); }
           | MethodBody Statement      { $$ = $1; $$->children.push_back($2); }
           | MethodBody Return         { $$ = $1; $$->children.push_back($2); }
           ;

Return : RETURN Expression { $$ = make_shared<Return>("Return", ""); $$->children.push_back($2); }
       ;

FormalParameterList : FormalParameter                           { $$ = make_shared<FormalParameterList>("FormalParameterList", ""); $$->children.push_back($1); }
                    | FormalParameterList COMMA FormalParameter { $$ = $1; $$->children.push_back($3); }
                    ;

FormalParameter : Type Identifier { $$ = make_shared<FormalParameter>("FormalParameter", ""); $$->children.push_back($1); $$->children.push_back($2); }
                ;

Type : INT LBRACKET RBRACKET { $$ = make_shared<Type>("Type", $1+$2+$3); }
     | BOOLEAN               { $$ = make_shared<Type>("Type", $1); }
     | INT                   { $$ = make_shared<Type>("Type", $1); }
     | Identifier            { $$ = make_shared<Type>("Type", ""); $$->children.push_back($1); }
     ;

Statements : Statement            { $$ = make_shared<Statement>("Statements", ""); $$->children.push_back($1); }
           | Statements Statement { $$ = $1; $$->children.push_back($2); }
           ;

Statement : LBRACE RBRACE              { $$ = make_shared<Statement>("Statement", "EMPTY"); }
          | LBRACE Statements RBRACE   { $$ = make_shared<Statement>("Statement", ""); $$->children.push_back($2); }
          | AssignStatement            { $$ = $1; }
          | ArrayAssignStatement       { $$ = $1; }
          | IfStatement                { $$ = $1; }
          | WhileStatement             { $$ = $1; }
          | PrintStatement             { $$ = $1; }
          ;

AssignStatement : Identifier ASSIGN Expression SEMI                                   { $$ = make_shared<AssignStatement>("AssignStatement", $2); $$->children.push_back($1); $$->children.push_back($3); }
                ;

ArrayAssignStatement : Identifier LBRACKET Expression RBRACKET ASSIGN Expression SEMI { $$ = make_shared<ArrayAssignStatement>("ArrayAssignStatement", $2+$4+$5); $$->children.push_back($1); $$->children.push_back($3); $$->children.push_back($6); }
                     ;

IfStatement : IF LPARENTHESE Expression RPARENTHESE Statement ElseStatement           { $$ = make_shared<IfStatement>("IfStatement", ""); $$->children.push_back($3); $$->children.push_back($5); $$->children.push_back($6); }
            ;

ElseStatement : ELSE Statement { $$ = make_shared<ElseStatement>("ElseStatement", ""); $$->children.push_back($2); }
              ;

WhileStatement : WHILE LPARENTHESE Expression RPARENTHESE Statement                   { $$ = make_shared<WhileStatement>("WhileStatement", ""); $$->children.push_back($3); $$->children.push_back($5); }
               ;

PrintStatement : SOPRINTLN LPARENTHESE Expression RPARENTHESE SEMI                    { $$ = make_shared<PrintStatement>("PrintStatement", $1); $$->children.push_back($3); }
               ;

Expression : PrimaryExpression                                                { $$ = make_shared<Expression>("Expression", ""); $$->children.push_back($1); }
           | LogicExpression                                                  { $$ = $1; }
           | CompareExpression                                                { $$ = $1; }
           | ArithExpression                                                  { $$ = $1; }
           | ArraySearchExpression                                            { $$ = $1; }
           | ArrayLengthExpression                                            { $$ = $1; }
           | Expression DOT Identifier LPARENTHESE RPARENTHESE                { $$ = $1; $$->children.push_back($3); }
           | Expression DOT Identifier LPARENTHESE ExpressionList RPARENTHESE { $$ = $1; $$->children.push_back($3); $$->children.push_back($5); }
           ;

LogicExpression : Expression AND Expression                       { $$ = make_shared<LogicExpression>("LogicExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                | Expression OR Expression                        { $$ = make_shared<LogicExpression>("LogicExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                ;

CompareExpression : Expression LT Expression                      { $$ = make_shared<CompareExpression>("CompareExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                  | Expression LET Expression                     { $$ = make_shared<CompareExpression>("CompareExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                  | Expression GT Expression                      { $$ = make_shared<CompareExpression>("CompareExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                  | Expression GET Expression                     { $$ = make_shared<CompareExpression>("CompareExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                  | Expression EQUAL Expression                   { $$ = make_shared<CompareExpression>("CompareExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                  | Expression NOTEQUAL Expression                { $$ = make_shared<CompareExpression>("CompareExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                  ;

ArithExpression : Expression ADD Expression                       { $$ = make_shared<ArithExpression>("ArithExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                | Expression SUB Expression                       { $$ = make_shared<ArithExpression>("ArithExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                | Expression MUL Expression                       { $$ = make_shared<ArithExpression>("ArithExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                | Expression DIV Expression                       { $$ = make_shared<ArithExpression>("ArithExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                ;

ArraySearchExpression : Expression LBRACKET Expression RBRACKET   { $$ = make_shared<ArraySearchExpression>("ArraySearchExpression", $2+$4); $$->children.push_back($1); $$->children.push_back($3); }
                      ;

ArrayLengthExpression : Expression DOT LENGTH                     { $$ = make_shared<ArrayLengthExpression>("ArrayLengthExpression", $2+$3); $$->children.push_back($1); }
                      ;

ExpressionList : Expression                      { $$ = make_shared<ExpressionList>("ExpressionList", ""); $$->children.push_back($1); }
               | ExpressionList COMMA Expression { $$ = $1; $$->children.push_back($3); }
               ;

PrimaryExpression : LPARENTHESE Expression RPARENTHESE     { $$ = make_shared<PrimaryExpression>("PrimaryExpression", ""); $$->children.push_back($2); }
                  | Identifier                             { $$ = make_shared<PrimaryExpression>("PrimaryExpression", ""); $$->children.push_back($1); }
                  | ArrayAllocExpression                   { $$ = $1; }
                  | AllocExpression                        { $$ = $1; }
                  | UnaryExpression                        { $$ = $1; }
                  | NUM                                    { $$ = make_shared<PrimaryExpression>("int", $1); }
                  | TRUE                                   { $$ = make_shared<PrimaryExpression>("boolean", $1); }
                  | FALSE                                  { $$ = make_shared<PrimaryExpression>("boolean", $1); }
                  | THIS                                   { $$ = make_shared<PrimaryExpression>("keyword", $1); }
                  ;

ArrayAllocExpression : NEW INT LBRACKET Expression RBRACKET   { $$ = make_shared<ArrayAllocExpression>("ArrayAllocExpression", $1+" "+$2+$3+$5); $$->children.push_back($4); }
                     ;

AllocExpression : NEW Identifier LPARENTHESE RPARENTHESE      { $$ = make_shared<AllocExpression>("AllocExpression", $1); $$->children.push_back($2); }
                ;

UnaryExpression : NOT Expression                              { $$ = make_shared<UnaryExpression>("UnaryExpression", $1); $$->children.push_back($2); }
                | SUB Expression                              { $$ = make_shared<UnaryExpression>("UnaryExpression", $1); $$->children.push_back($2); }
                ;

Identifier : IDENTIFIER { $$ = make_shared<Identifier>("Identifier", $1); }
           ;
%%