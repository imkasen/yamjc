#include "ast/identifier.h"

#include <utility>
using std::string;

Identifier::Identifier() : Node() {}
Identifier::Identifier(string t, string v) : Node(std::move(t), std::move(v)) {}

std::optional<string> Identifier::generateST()
{
    return this->getValue();
}
