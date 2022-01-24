#include "ast/statements/array_assign_statement.h"
using std::string;

ArrayAssignStatement::ArrayAssignStatement() : Node() {}
ArrayAssignStatement::ArrayAssignStatement(string t, string v) : Node(std::move(t), std::move(v)) {}
