#include "ast/method_body.h"

#include <utility>

MethodBody::MethodBody() : Node() {}
MethodBody::MethodBody(std::string t, std::string v) : Node(std::move(t), std::move(v)) {}

std::optional<std::string> MethodBody::generateST()
{
    for (auto &child: this->children)
    {
        if (child->getType() == "VarDeclaration")
        {
            child->generateST();
        }
    }

    return std::nullopt;
}
