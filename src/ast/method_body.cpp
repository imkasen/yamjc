#include "ast/method_body.h"

MethodBody::MethodBody() : Node() {}
MethodBody::MethodBody(std::string t, std::string v) : Node(std::move(t), std::move(v)) {}

/*
 *      "MethodBody"
 *           |
 * "PrintStatement:System.out.println"
 *
 * @brief: Do nothing.
 *
 *      "MethodBody"
 *           |
 *    "VarDeclaration"
 *
 * @brief: Traverse nodes.
 * @return: std::nullopt
 */
std::optional<std::string> MethodBody::generateST() {
    for (const auto &child : this->children) {
        if (child->getType() == "VarDeclaration") {
            child->generateST();
        }
    }

    return std::nullopt;
}

/*
 * @brief: Traverse nodes.
 * @return: nullopt
 */
std::optional<std::string> MethodBody::checkSemantics() {
    for (auto child : this->children) {
        child->checkSemantics();
    }
    return std::nullopt;
}
