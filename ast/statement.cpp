#include "statement.h"

Statement::Statement() : Node() {}

Statement::Statement(std::string t, std::string v) : Node(t, v) {}

std::optional<std::string> Statement::execute()
{
    for (auto child: children)
    {
        child.execute();
    }

    return std::nullopt;
}
