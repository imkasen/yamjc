#include "ast/statements/if_statement.h"
using std::string;

IfStatement::IfStatement() : Statement() {}
IfStatement::IfStatement(string t, string v) : Statement(std::move(t), std::move(v)) {}
