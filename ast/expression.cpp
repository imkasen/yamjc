#include "expression.h"

Expression::Expression() : Node() {}

Expression::Expression(std::string t, std::string v) : Node(t, v) {}

std::optional<std::string> Expression::execute()
{
    for (auto child: children)
    {
        child.execute();
    }

    return std::nullopt;
}
