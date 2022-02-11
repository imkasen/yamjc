%skeleton "lalr1.cc"
%require "3.2"
%language "c++"
%defines
%define parse.error verbose
%define api.value.type variant
%define api.token.constructor

%code requires {
  #include "ast/nodes.h"
}

%code provides {
  extern FILE* yyin;
}

%code {
  #include "main.h"

  std::shared_ptr<Node> root;
}

%token <std::string> CLASS PUBLIC STATIC VOID MAIN STRING EXTENDS LENGTH NEW THIS RETURN
%token <std::string> IF ELSE WHILE
%token <std::string> SOPRINTLN
%token <std::string> INT BOOLEAN
%token <std::string> AND OR NOT EQUAL NOTEQUAL
%token <std::string> TRUE FALSE
%token <std::string> LT LET GT GET
%token <std::string> ADD SUB MUL DIV
%token <std::string> LPARENTHESE RPARENTHESE LBRACKET RBRACKET LBRACE RBRACE
%token <std::string> SEMI COMMA ASSIGN DOT
%token <std::string> NUM IDENTIFIER

%token END 0 "end of file"

%right ASSIGN
%left OR
%left AND
%left EQUAL NOTEQUAL
%left LT LET GT GET
%left ADD SUB
%left MUL DIV
%right NOT
%left LBRACKET RBRACKET LBRACE RBRACE LPARENTHESE RPARENTHESE DOT

%start Goal

%type <std::shared_ptr<Goal>> Goal
%type <std::shared_ptr<MainClass>> MainClass
%type <std::shared_ptr<MethodBody>> MethodBody
%type <std::shared_ptr<Type>> Type
%type <std::shared_ptr<Return>> Return
%type <std::shared_ptr<Identifier>> Identifier

%type <std::shared_ptr<Node>> ClassDeclarations
%type <std::shared_ptr<ClassDeclaration>> ClassDeclaration
%type <std::shared_ptr<ClassExtendsDeclaration>> ClassExtendsDeclaration
%type <std::shared_ptr<Declarations>> Declarations
%type <std::shared_ptr<VarDeclaration>> VarDeclaration
%type <std::shared_ptr<MethodDeclaration>> MethodDeclaration

%type <std::shared_ptr<FormalParameterList>> FormalParameterList
%type <std::shared_ptr<FormalParameter>> FormalParameter

%type <std::shared_ptr<Expression>> Expression
%type <std::shared_ptr<ExpressionList>> ExpressionList
%type <std::shared_ptr<LogicExpression>> LogicExpression
%type <std::shared_ptr<CompareExpression>> CompareExpression
%type <std::shared_ptr<ArithExpression>> ArithExpression
%type <std::shared_ptr<ArraySearchExpression>> ArraySearchExpression
%type <std::shared_ptr<ArrayLengthExpression>> ArrayLengthExpression

%type <std::shared_ptr<PrimaryExpression>> PrimaryExpression
%type <std::shared_ptr<ArrayAllocExpression>> ArrayAllocExpression
%type <std::shared_ptr<AllocExpression>> AllocExpression
%type <std::shared_ptr<UnaryExpression>> UnaryExpression

%type <std::shared_ptr<Statement>> Statements Statement
%type <std::shared_ptr<AssignStatement>> AssignStatement
%type <std::shared_ptr<ArrayAssignStatement>> ArrayAssignStatement
%type <std::shared_ptr<IfStatement>> IfStatement
%type <std::shared_ptr<ElseStatement>> ElseStatement
%type <std::shared_ptr<WhileStatement>> WhileStatement
%type <std::shared_ptr<PrintStatement>> PrintStatement

%%

Goal : MainClass              { $$ = std::make_shared<Goal>("Goal", ""); $$->children.push_back($1); root = $$; }
     | Goal ClassDeclarations { $$ = $1; $$->children.push_back($2); root = $$; }
     | END                    { $$ = std::make_shared<Goal>("Goal", "EOF"); root = $$; }
     ;

MainClass : CLASS Identifier LBRACE PUBLIC STATIC VOID MAIN LPARENTHESE STRING LBRACKET RBRACKET Identifier RPARENTHESE LBRACE RBRACE RBRACE
              { $$ = std::make_shared<MainClass>("MainClass", ""); $$->children.push_back($2); $$->children.push_back($12); }
          | CLASS Identifier LBRACE PUBLIC STATIC VOID MAIN LPARENTHESE STRING LBRACKET RBRACKET Identifier RPARENTHESE LBRACE MethodBody RBRACE RBRACE
              { $$ = std::make_shared<MainClass>("MainClass", ""); $$->children.push_back($2); $$->children.push_back($12); $$->children.push_back($15); }
          ;

ClassDeclarations : ClassDeclaration        { $$ = $1; }
                  | ClassExtendsDeclaration { $$ = $1; }
                  ;

ClassDeclaration : CLASS Identifier LBRACE RBRACE              { $$ = std::make_shared<ClassDeclaration>("ClassDeclaration", ""); $$->children.push_back($2); }
                 | CLASS Identifier LBRACE Declarations RBRACE { $$ = std::make_shared<ClassDeclaration>("ClassDeclaration", ""); $$->children.push_back($2); $$->children.push_back($4); }
                 ;

ClassExtendsDeclaration : CLASS Identifier EXTENDS Identifier LBRACE RBRACE              { $$ = std::make_shared<ClassExtendsDeclaration>("ClassExtendsDeclaration", ""); $$->children.push_back($2); $$->children.push_back($4); }
                        | CLASS Identifier EXTENDS Identifier LBRACE Declarations RBRACE { $$ = std::make_shared<ClassExtendsDeclaration>("ClassExtendsDeclaration", ""); $$->children.push_back($2); $$->children.push_back($4); $$->children.push_back($6); }
                        ;

Declarations : VarDeclaration                 { $$ = std::make_shared<Declarations>("Declarations", ""); $$->children.push_back($1); }
             | MethodDeclaration              { $$ = std::make_shared<Declarations>("Declarations", ""); $$->children.push_back($1); }
             | Declarations VarDeclaration    { $$ = $1; $$->children.push_back($2); }
             | Declarations MethodDeclaration { $$ = $1; $$->children.push_back($2); }
             ;

VarDeclaration : Type Identifier SEMI { $$ = std::make_shared<VarDeclaration>("VarDeclaration", ""); $$->children.push_back($1); $$->children.push_back($2); }
               ;

MethodDeclaration : PUBLIC Type Identifier LPARENTHESE RPARENTHESE LBRACE Return SEMI RBRACE
                    { $$ = std::make_shared<MethodDeclaration>("MethodDeclaration", ""); $$->children.push_back($2); $$->children.push_back($3); $$->children.push_back($7); }
                  | PUBLIC Type Identifier LPARENTHESE FormalParameterList RPARENTHESE LBRACE Return SEMI RBRACE
                    { $$ = std::make_shared<MethodDeclaration>("MethodDeclaration", ""); $$->children.push_back($2); $$->children.push_back($3); $$->children.push_back($5); $$->children.push_back($8); }
                  | PUBLIC Type Identifier LPARENTHESE RPARENTHESE LBRACE MethodBody SEMI RBRACE
                    { $$ = std::make_shared<MethodDeclaration>("MethodDeclaration", ""); $$->children.push_back($2); $$->children.push_back($3); $$->children.push_back($7); }
                  | PUBLIC Type Identifier LPARENTHESE FormalParameterList RPARENTHESE LBRACE MethodBody SEMI RBRACE
                    { $$ = std::make_shared<MethodDeclaration>("MethodDeclaration", ""); $$->children.push_back($2); $$->children.push_back($3); $$->children.push_back($5); $$->children.push_back($8); }
                  ;

MethodBody : VarDeclaration            { $$ = std::make_shared<MethodBody>("MethodBody", ""); $$->children.push_back($1); }
           | Statement                 { $$ = std::make_shared<MethodBody>("MethodBody", ""); $$->children.push_back($1); }
           | MethodBody VarDeclaration { $$ = $1; $$->children.push_back($2); }
           | MethodBody Statement      { $$ = $1; $$->children.push_back($2); }
           | MethodBody Return         { $$ = $1; $$->children.push_back($2); }
           ;

Return : RETURN Expression { $$ = std::make_shared<Return>("Return", ""); $$->children.push_back($2); }
       ;

FormalParameterList : FormalParameter                           { $$ = std::make_shared<FormalParameterList>("FormalParameterList", ""); $$->children.push_back($1); }
                    | FormalParameterList COMMA FormalParameter { $$ = $1; $$->children.push_back($3); }
                    ;

FormalParameter : Type Identifier { $$ = std::make_shared<FormalParameter>("FormalParameter", ""); $$->children.push_back($1); $$->children.push_back($2); }
                ;

Type : INT LBRACKET RBRACKET { $$ = std::make_shared<Type>("Type", $1+$2+$3); }
     | BOOLEAN               { $$ = std::make_shared<Type>("Type", $1); }
     | INT                   { $$ = std::make_shared<Type>("Type", $1); }
     | Identifier            { $$ = std::make_shared<Type>("Type", ""); $$->children.push_back($1); }
     ;

Statements : Statement            { $$ = std::make_shared<Statement>("Statements", ""); $$->children.push_back($1); }
           | Statements Statement { $$ = $1; $$->children.push_back($2); }
           ;

Statement : LBRACE RBRACE              { $$ = std::make_shared<Statement>("Statement", "EMPTY"); }
          | LBRACE Statements RBRACE   { $$ = std::make_shared<Statement>("Statement", ""); $$->children.push_back($2); }
          | AssignStatement            { $$ = $1; }
          | ArrayAssignStatement       { $$ = $1; }
          | IfStatement                { $$ = $1; }
          | WhileStatement             { $$ = $1; }
          | PrintStatement             { $$ = $1; }
          ;

AssignStatement : Identifier ASSIGN Expression SEMI                                   { $$ = std::make_shared<AssignStatement>("AssignStatement", $2); $$->children.push_back($1); $$->children.push_back($3); }
                ;

ArrayAssignStatement : Identifier LBRACKET Expression RBRACKET ASSIGN Expression SEMI { $$ = std::make_shared<ArrayAssignStatement>("ArrayAssignStatement", $2+$4+$5); $$->children.push_back($1); $$->children.push_back($3); $$->children.push_back($6); }
                     ;

IfStatement : IF LPARENTHESE Expression RPARENTHESE Statement ElseStatement           { $$ = std::make_shared<IfStatement>("IfStatement", ""); $$->children.push_back($3); $$->children.push_back($5); $$->children.push_back($6); }
            ;

ElseStatement : ELSE Statement { $$ = std::make_shared<ElseStatement>("ElseStatement", ""); $$->children.push_back($2); }
              ;

WhileStatement : WHILE LPARENTHESE Expression RPARENTHESE Statement                   { $$ = std::make_shared<WhileStatement>("WhileStatement", ""); $$->children.push_back($3); $$->children.push_back($5); }
               ;

PrintStatement : SOPRINTLN LPARENTHESE Expression RPARENTHESE SEMI                    { $$ = std::make_shared<PrintStatement>("PrintStatement", $1); $$->children.push_back($3); }
               ;

Expression : PrimaryExpression                                                { $$ = std::make_shared<Expression>("Expression", ""); $$->children.push_back($1); }
           | LogicExpression                                                  { $$ = $1; }
           | CompareExpression                                                { $$ = $1; }
           | ArithExpression                                                  { $$ = $1; }
           | ArraySearchExpression                                            { $$ = $1; }
           | ArrayLengthExpression                                            { $$ = $1; }
           | Expression DOT Identifier LPARENTHESE RPARENTHESE                { $$ = $1; $$->children.push_back($3); }
           | Expression DOT Identifier LPARENTHESE ExpressionList RPARENTHESE { $$ = $1; $$->children.push_back($3); $$->children.push_back($5); }
           ;

LogicExpression : Expression AND Expression                       { $$ = std::make_shared<LogicExpression>("LogicExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                | Expression OR Expression                        { $$ = std::make_shared<LogicExpression>("LogicExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                ;

CompareExpression : Expression LT Expression                      { $$ = std::make_shared<CompareExpression>("CompareExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                  | Expression LET Expression                     { $$ = std::make_shared<CompareExpression>("CompareExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                  | Expression GT Expression                      { $$ = std::make_shared<CompareExpression>("CompareExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                  | Expression GET Expression                     { $$ = std::make_shared<CompareExpression>("CompareExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                  | Expression EQUAL Expression                   { $$ = std::make_shared<CompareExpression>("CompareExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                  | Expression NOTEQUAL Expression                { $$ = std::make_shared<CompareExpression>("CompareExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                  ;

ArithExpression : Expression ADD Expression                       { $$ = std::make_shared<ArithExpression>("ArithExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                | Expression SUB Expression                       { $$ = std::make_shared<ArithExpression>("ArithExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                | Expression MUL Expression                       { $$ = std::make_shared<ArithExpression>("ArithExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                | Expression DIV Expression                       { $$ = std::make_shared<ArithExpression>("ArithExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                ;

ArraySearchExpression : Expression LBRACKET Expression RBRACKET   { $$ = std::make_shared<ArraySearchExpression>("ArraySearchExpression", $2+$4); $$->children.push_back($1); $$->children.push_back($3); }
                      ;

ArrayLengthExpression : Expression DOT LENGTH                     { $$ = std::make_shared<ArrayLengthExpression>("ArrayLengthExpression", $2+$3); $$->children.push_back($1); }
                      ;

ExpressionList : Expression                      { $$ = std::make_shared<ExpressionList>("ExpressionList", ""); $$->children.push_back($1); }
               | ExpressionList COMMA Expression { $$ = $1; $$->children.push_back($3); }
               ;

PrimaryExpression : LPARENTHESE Expression RPARENTHESE     { $$ = std::make_shared<PrimaryExpression>("PrimaryExpression", ""); $$->children.push_back($2); }
                  | Identifier                             { $$ = std::make_shared<PrimaryExpression>("PrimaryExpression", ""); $$->children.push_back($1); }
                  | ArrayAllocExpression                   { $$ = $1; }
                  | AllocExpression                        { $$ = $1; }
                  | UnaryExpression                        { $$ = $1; }
                  | NUM                                    { $$ = std::make_shared<PrimaryExpression>("int", $1); }
                  | TRUE                                   { $$ = std::make_shared<PrimaryExpression>("boolean", $1); }
                  | FALSE                                  { $$ = std::make_shared<PrimaryExpression>("boolean", $1); }
                  | THIS                                   { $$ = std::make_shared<PrimaryExpression>("keyword", $1); }
                  ;

ArrayAllocExpression : NEW INT LBRACKET Expression RBRACKET   { $$ = std::make_shared<ArrayAllocExpression>("ArrayAllocExpression", $1+" "+$2+$3+$5); $$->children.push_back($4); }
                     ;

AllocExpression : NEW Identifier LPARENTHESE RPARENTHESE      { $$ = std::make_shared<AllocExpression>("AllocExpression", $1); $$->children.push_back($2); }
                ;

UnaryExpression : NOT Expression                              { $$ = std::make_shared<UnaryExpression>("UnaryExpression", $1); $$->children.push_back($2); }
                | SUB Expression                              { $$ = std::make_shared<UnaryExpression>("UnaryExpression", $1); $$->children.push_back($2); }
                ;

Identifier : IDENTIFIER { $$ = std::make_shared<Identifier>("Identifier", $1); }
           ;
%%