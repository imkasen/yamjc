#include "method_body.h"

MethodBody::MethodBody() : Node() {}

MethodBody::MethodBody(std::string t, std::string v) : Node(t, v) {}

std::optional<std::string> MethodBody::execute()
{
    for (auto child: children)
    {
        child.execute();
    }

    return std::nullopt;
}
