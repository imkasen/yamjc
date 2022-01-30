#include "ast/expressions/expression_list.h"
using std::string;

ExpressionList::ExpressionList() : Node() {}
ExpressionList::ExpressionList(string t, string v) : Node(std::move(t), std::move(v)) {}

/*
 * @return: string
 */
std::optional<std::string> ExpressionList::checkSemantics() {
    string parameter_type_list;

    // Splice formal parameter types, "xxx xxx ..."
    for (const auto &child : this->children) {
        parameter_type_list += child->checkSemantics().value_or("") + " ";
    }

    return parameter_type_list;
}
