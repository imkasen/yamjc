#include "ast/statement.h"

Statement::Statement() : Node() {}
Statement::Statement(std::string t, std::string v) : Node(std::move(t), std::move(v)) {}
