#include "ast/statements/while_statement.h"
using std::string;

WhileStatement::WhileStatement() : Statement() {}
WhileStatement::WhileStatement(string t, string v) : Statement(std::move(t), std::move(v)) {}
