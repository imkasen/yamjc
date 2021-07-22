#include "statement.h"

Statement::Statement() : Node() {}

Statement::Statement(std::string t, std::string v) : Node(t, v) {}

std::optional<std::string> Statement::generateST()
{
    for (auto child: children)
    {
        child.generateST();
    }

    return std::nullopt;
}
