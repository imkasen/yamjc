#include "ast/statement.h"

#include <utility>

Statement::Statement() : Node() {}
Statement::Statement(std::string t, std::string v) : Node(std::move(t), std::move(v)) {}
