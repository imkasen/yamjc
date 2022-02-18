#include "ast/method_body.h"
using ast::MethodBody;
using std::string;

/*
       "MethodBody"
            |          \
      "VarDeclaration"  ...
 */

MethodBody::MethodBody() : Node() {}
MethodBody::MethodBody(string t, string v) : Node(std::move(t), std::move(v)) {}

/*
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
