#include "expression.h"

Expression::Expression() : Node() {}

Expression::Expression(std::string t, std::string v) : Node(t, v) {}

std::optional<std::string> Expression::generateST()
{
    for (auto child: children)
    {
        child.generateST();
    }

    return std::nullopt;
}
