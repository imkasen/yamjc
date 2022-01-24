#include "ast/statements/else_statement.h"
using std::string;

ElseStatement::ElseStatement() : Statement() {}
ElseStatement::ElseStatement(string t, string v) : Statement(std::move(t), std::move(v)) {}
