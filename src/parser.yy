%skeleton "lalr1.cc"
%require "3.2"
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
  
  Node *root;
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
%left LBRACKET LBRACE LPARENTHESE DOT

%start Goal

%type <Goal *> Goal
%type <MainClass *> MainClass
%type <MethodBody *> MethodBody
%type <Type *> Type
%type <Return *> Return
%type <Identifier *> Identifier

%type <Node *> ClassDeclarations
%type <ClassDeclaration *> ClassDeclaration
%type <ClassExtendsDeclaration *> ClassExtendsDeclaration
%type <Declarations *> Declarations
%type <VarDeclaration *> VarDeclaration
%type <MethodDeclaration *> MethodDeclaration

%type <FormalParameterList *> FormalParameterList
%type <FormalParameter *> FormalParameter

%type <Expression *> Expression
%type <ExpressionList *> ExpressionList
%type <LogicExpression *> LogicExpression
%type <CompareExpression *> CompareExpression
%type <ArithExpression *> ArithExpression
%type <ArraySearchExpression *> ArraySearchExpression
%type <ArrayLengthExpression *> ArrayLengthExpression

%type <PrimaryExpression *> PrimaryExpression
%type <ArrayAllocExpression *> ArrayAllocExpression
%type <AllocExpression *> AllocExpression
%type <UnaryExpression *> UnaryExpression

%type <Statement *> Statements Statement
%type <AssignStatement *> AssignStatement
%type <ArrayAssignStatement *> ArrayAssignStatement
%type <IfStatement *> IfStatement
%type <ElseStatement *> ElseStatement
%type <WhileStatement *> WhileStatement
%type <PrintStatement *> PrintStatement

%%

Goal : MainClass              { $$ = new Goal("Goal", ""); $$->children.push_back($1); root = $$; }
     | Goal ClassDeclarations { $$ = $1; $$->children.push_back($2); root = $$; }
     | END                    { $$ = new Goal("Goal", "EOF"); root = $$; }
     ;

MainClass : CLASS Identifier LBRACE PUBLIC STATIC VOID MAIN LPARENTHESE STRING LBRACKET RBRACKET Identifier RPARENTHESE LBRACE RBRACE RBRACE
              { $$ = new MainClass("MainClass", ""); $$->children.push_back($2); $$->children.push_back($12); }
          | CLASS Identifier LBRACE PUBLIC STATIC VOID MAIN LPARENTHESE STRING LBRACKET RBRACKET Identifier RPARENTHESE LBRACE MethodBody RBRACE RBRACE
              { $$ = new MainClass("MainClass", ""); $$->children.push_back($2); $$->children.push_back($12); $$->children.push_back($15); }
          ;

ClassDeclarations : ClassDeclaration        { $$ = $1; }
                  | ClassExtendsDeclaration { $$ = $1; }
                  ;

ClassDeclaration : CLASS Identifier LBRACE RBRACE              { $$ = new ClassDeclaration("ClassDeclaration", ""); $$->children.push_back($2); }
                 | CLASS Identifier LBRACE Declarations RBRACE { $$ = new ClassDeclaration("ClassDeclaration", ""); $$->children.push_back($2); $$->children.push_back($4); }
                 ;

ClassExtendsDeclaration : CLASS Identifier EXTENDS Identifier LBRACE RBRACE              { $$ = new ClassExtendsDeclaration("ClassExtendsDeclaration", $3); $$->children.push_back($2); $$->children.push_back($4); }
                        | CLASS Identifier EXTENDS Identifier LBRACE Declarations RBRACE { $$ = new ClassExtendsDeclaration("ClassExtendsDeclaration", $3); $$->children.push_back($2); $$->children.push_back($4); $$->children.push_back($6); }
                        ;

Declarations : VarDeclaration                 { $$ = new Declarations("Declarations", ""); $$->children.push_back($1); }
             | MethodDeclaration              { $$ = new Declarations("Declarations", ""); $$->children.push_back($1); }
             | Declarations VarDeclaration    { $$ = $1; $$->children.push_back($2); }
             | Declarations MethodDeclaration { $$ = $1; $$->children.push_back($2); }
             ;

VarDeclaration : Type Identifier SEMI { $$ = new VarDeclaration("VarDeclaration", ""); $$->children.push_back($1); $$->children.push_back($2); }
               ;

MethodDeclaration : PUBLIC Type Identifier LPARENTHESE RPARENTHESE LBRACE Return SEMI RBRACE
                    { $$ = new MethodDeclaration("MethodDeclaration", ""); $$->children.push_back($2); $$->children.push_back($3); $$->children.push_back($7); }
                  | PUBLIC Type Identifier LPARENTHESE FormalParameterList RPARENTHESE LBRACE Return SEMI RBRACE
                    { $$ = new MethodDeclaration("MethodDeclaration", ""); $$->children.push_back($2); $$->children.push_back($3); $$->children.push_back($5); $$->children.push_back($8); }
                  | PUBLIC Type Identifier LPARENTHESE RPARENTHESE LBRACE MethodBody SEMI RBRACE
                    { $$ = new MethodDeclaration("MethodDeclaration", ""); $$->children.push_back($2); $$->children.push_back($3); $$->children.push_back($7); }
                  | PUBLIC Type Identifier LPARENTHESE FormalParameterList RPARENTHESE LBRACE MethodBody SEMI RBRACE
                    { $$ = new MethodDeclaration("MethodDeclaration", ""); $$->children.push_back($2); $$->children.push_back($3); $$->children.push_back($5); $$->children.push_back($8); }
                  ;

MethodBody : VarDeclaration            { $$ = new MethodBody("MethodBody", ""); $$->children.push_back($1); }
           | Statement                 { $$ = new MethodBody("MethodBody", ""); $$->children.push_back($1); }
           | MethodBody VarDeclaration { $$ = $1; $$->children.push_back($2); }
           | MethodBody Statement      { $$ = $1; $$->children.push_back($2); }
           | MethodBody Return         { $$ = $1; $$->children.push_back($2); }
           ;

Return : RETURN Expression { $$ = new Return("Return", ""); $$->children.push_back($2); }
       ;

FormalParameterList : FormalParameter                           { $$ = new FormalParameterList("FormalParameterList", ""); $$->children.push_back($1); }
                    | FormalParameterList COMMA FormalParameter { $$ = $1; $$->children.push_back($3); }
                    ;

FormalParameter : Type Identifier { $$ = new FormalParameter("FormalParameter", ""); $$->children.push_back($1); $$->children.push_back($2); }
                ;

Type : INT LBRACKET RBRACKET { $$ = new Type("Type", $1+$2+$3); }
     | BOOLEAN               { $$ = new Type("Type", $1); }
     | INT                   { $$ = new Type("Type", $1); }
     | Identifier            { $$ = new Type("Type", ""); $$->children.push_back($1); }
     ;

Statements : Statement            { $$ = new Statement("Statements", ""); $$->children.push_back($1); }
           | Statements Statement { $$ = $1; $$->children.push_back($2); }
           ;

Statement : LBRACE RBRACE              { $$ = new Statement("Statement", "EMPTY"); }
          | LBRACE Statements RBRACE   { $$ = new Statement("Statement", ""); $$->children.push_back($2); }
          | AssignStatement            { $$ = $1; }
          | ArrayAssignStatement       { $$ = $1; }
          | IfStatement                { $$ = $1; }
          | WhileStatement             { $$ = $1; }
          | PrintStatement             { $$ = $1; }
          ;

AssignStatement : Identifier ASSIGN Expression SEMI                                   { $$ = new AssignStatement("AssignStatement", $2); $$->children.push_back($1); $$->children.push_back($3); }
                ;

ArrayAssignStatement : Identifier LBRACKET Expression RBRACKET ASSIGN Expression SEMI { $$ = new ArrayAssignStatement("ArrayAssignStatement", $2+$4+$5); $$->children.push_back($1); $$->children.push_back($3); $$->children.push_back($6); }
                     ;

IfStatement : IF LPARENTHESE Expression RPARENTHESE Statement ElseStatement           { $$ = new IfStatement("IfStatement", ""); $$->children.push_back($3); $$->children.push_back($5); $$->children.push_back($6); }
            ;

ElseStatement : ELSE Statement { $$ = new ElseStatement("ElseStatement", ""); $$->children.push_back($2); }
              ;

WhileStatement : WHILE LPARENTHESE Expression RPARENTHESE Statement                   { $$ = new WhileStatement("WhileStatement", ""); $$->children.push_back($3); $$->children.push_back($5); }
               ;

PrintStatement : SOPRINTLN LPARENTHESE Expression RPARENTHESE SEMI                    { $$ = new PrintStatement("PrintStatement", $1); $$->children.push_back($3); }
               ;

Expression : PrimaryExpression                                                { $$ = new Expression("Expression", ""); $$->children.push_back($1); }
           | LogicExpression                                                  { $$ = $1; }
           | CompareExpression                                                { $$ = $1; }
           | ArithExpression                                                  { $$ = $1; }
           | ArraySearchExpression                                            { $$ = $1; }
           | ArrayLengthExpression                                            { $$ = $1; }
           | Expression DOT Identifier LPARENTHESE RPARENTHESE                { $$ = $1; $$->children.push_back($3); }
           | Expression DOT Identifier LPARENTHESE ExpressionList RPARENTHESE { $$ = $1; $$->children.push_back($3); $$->children.push_back($5); }
           ;

LogicExpression : Expression AND Expression                       { $$ = new LogicExpression("LogicExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                | Expression OR Expression                        { $$ = new LogicExpression("LogicExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                ;

CompareExpression : Expression LT Expression                      { $$ = new CompareExpression("CompareExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                  | Expression LET Expression                     { $$ = new CompareExpression("CompareExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                  | Expression GT Expression                      { $$ = new CompareExpression("CompareExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                  | Expression GET Expression                     { $$ = new CompareExpression("CompareExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                  | Expression EQUAL Expression                   { $$ = new CompareExpression("CompareExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                  | Expression NOTEQUAL Expression                { $$ = new CompareExpression("CompareExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                  ;

ArithExpression : Expression ADD Expression                       { $$ = new ArithExpression("ArithExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                | Expression SUB Expression                       { $$ = new ArithExpression("ArithExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                | Expression MUL Expression                       { $$ = new ArithExpression("ArithExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                | Expression DIV Expression                       { $$ = new ArithExpression("ArithExpression", $2); $$->children.push_back($1); $$->children.push_back($3); }
                ;

ArraySearchExpression : Expression LBRACKET Expression RBRACKET   { $$ = new ArraySearchExpression("ArraySearchExpression", $2+$4); $$->children.push_back($1); $$->children.push_back($3); }
                      ;

ArrayLengthExpression : Expression DOT LENGTH                     { $$ = new ArrayLengthExpression("ArrayLengthExpression", $2+$3); $$->children.push_back($1); }
                      ;

ExpressionList : Expression                      { $$ = new ExpressionList("ExpressionList", ""); $$->children.push_back($1); }
               | ExpressionList COMMA Expression { $$ = $1; $$->children.push_back($3); }
               ;

PrimaryExpression : LPARENTHESE Expression RPARENTHESE     { $$ = new PrimaryExpression("PrimaryExpression", ""); $$->children.push_back($2); }
                  | Identifier                             { $$ = new PrimaryExpression("PrimaryExpression", ""); $$->children.push_back($1); }
                  | ArrayAllocExpression                   { $$ = $1; }
                  | AllocExpression                        { $$ = $1; }
                  | UnaryExpression                        { $$ = $1; }
                  | NUM                                    { $$ = new PrimaryExpression("int", $1); }
                  | TRUE                                   { $$ = new PrimaryExpression("boolean", $1); }
                  | FALSE                                  { $$ = new PrimaryExpression("boolean", $1); }
                  | THIS                                   { $$ = new PrimaryExpression("keyword", $1); }
                  ;

ArrayAllocExpression : NEW INT LBRACKET Expression RBRACKET   { $$ = new ArrayAllocExpression("ArrayAllocExpression", $1+" "+$2+$3+$5); $$->children.push_back($4); }
                     ;

AllocExpression : NEW Identifier LPARENTHESE RPARENTHESE      { $$ = new AllocExpression("AllocExpression", $1); $$->children.push_back($2); }
                ;

UnaryExpression : NOT Expression                              { $$ = new UnaryExpression("UnaryExpression", $1); $$->children.push_back($2); }
                ;

Identifier : IDENTIFIER { $$ = new Identifier("Identifier", $1); }
           ;
%%