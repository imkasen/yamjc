#include "ast/statements/assign_statement.h"
using std::string;

AssignStatement::AssignStatement() : Node() {}
AssignStatement::AssignStatement(string t, string v) : Node(std::move(t), std::move(v)) {}
