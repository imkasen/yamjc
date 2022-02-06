#include "ast/statements/statement.h"
using std::string;

Statement::Statement() : Node() {}
Statement::Statement(string t, string v) : Node(std::move(t), std::move(v)) {}

/*
 * @brief: It will not be called at all, do nothing.
 * @return: std::nullopt
 */
std::optional<string> Statement::generateST() {
    return std::nullopt;
}