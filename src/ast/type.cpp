#include "ast/type.h"

#include <utility>
using std::string;

Type::Type() : Node() {}
Type::Type(string t, string v) : Node(std::move(t), std::move(v)) {}

std::optional<string> Type::generateST()
{
    if (!this->getValue().empty() && this->children.empty()) // has value && no children
    {
        return this->getValue();
    }
    else if (this->getValue().empty() && this->children.size() == 1) // no value && has one "Identifier" child
    {
        return this->children.at(0)->generateST().value_or("Unknown");
    }

    return std::nullopt;
}
