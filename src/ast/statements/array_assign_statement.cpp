#include "ast/statements/array_assign_statement.h"
using std::string;

ArrayAssignStatement::ArrayAssignStatement() : Statement() {}
ArrayAssignStatement::ArrayAssignStatement(string t, string v) : Statement(std::move(t), std::move(v)) {}
