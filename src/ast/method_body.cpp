#include "ast/method_body.h"
using std::string;

MethodBody::MethodBody() : Node() {}
MethodBody::MethodBody(string t, string v) : Node(std::move(t), std::move(v)) {}

/*
 *      "MethodBody"
 *           |          \
 *    "VarDeclaration"  ...
 *
 * @brief: Traverse nodes.
 * @return: std::nullopt
 */
std::optional<string> MethodBody::generateST() {
    for (const auto &child : this->children) {
        if (child->getType() == "VarDeclaration") {
            child->generateST();
        }
    }
    return std::nullopt;
}
