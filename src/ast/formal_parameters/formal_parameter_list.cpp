#include "ast/formal_parameters/formal_parameter_list.h"
using ast::FormalParameterList;
using std::size_t;
using std::string;

FormalParameterList::FormalParameterList(string t, string v) : Node(std::move(t), std::move(v)) {}

/*
 * @brief: Traverse children nodes.
 * @return: std::nullopt
 */
std::optional<string> FormalParameterList::generateST() {
    for (const auto &child : this->children) {
        child->generateST();
    }
    return std::nullopt;
}

/*
 * @brief: It will not be called at all, do nothing.
 * @return: std::nullopt
 */
std::optional<string> FormalParameterList::checkSemantics() {
    return std::nullopt;
}

/*
 * @brief: Traverse children nodes.
 * @return: std::nullopt
 */
std::optional<IRReturnVal> FormalParameterList::generateIR() {
    for (const auto &child : this->children) {
        child->generateIR();
    }
    return std::nullopt;
}
