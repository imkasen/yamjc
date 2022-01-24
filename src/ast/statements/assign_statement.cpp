#include "ast/statements/assign_statement.h"
using std::string;

AssignStatement::AssignStatement() : Statement() {}
AssignStatement::AssignStatement(string t, string v) : Statement(std::move(t), std::move(v)) {}
