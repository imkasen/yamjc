#include "ast/statements/if_statement.h"
using std::string;

IfStatement::IfStatement() : Node() {}
IfStatement::IfStatement(string t, string v) : Node(std::move(t), std::move(v)) {}
