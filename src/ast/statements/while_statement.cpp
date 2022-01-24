#include "ast/statements/while_statement.h"
using std::string;

WhileStatement::WhileStatement() : Node() {}
WhileStatement::WhileStatement(string t, string v) : Node(std::move(t), std::move(v)) {}
