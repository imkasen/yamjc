#include "ast/statements/print_statement.h"
using std::string;

PrintStatement::PrintStatement() : Node() {}
PrintStatement::PrintStatement(string t, string v) : Node(std::move(t), std::move(v)) {}
