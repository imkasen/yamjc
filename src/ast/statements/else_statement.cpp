#include "ast/statements/else_statement.h"
using std::string;

ElseStatement::ElseStatement() : Node() {}
ElseStatement::ElseStatement(string t, string v) : Node(std::move(t), std::move(v)) {}
