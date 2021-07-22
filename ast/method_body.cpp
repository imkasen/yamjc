#include "method_body.h"

MethodBody::MethodBody() : Node() {}

MethodBody::MethodBody(std::string t, std::string v) : Node(t, v) {}

std::optional<std::string> MethodBody::generateST()
{
    for (auto child: children)
    {
        child.generateST();
    }

    return std::nullopt;
}
