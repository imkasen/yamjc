#include "identifier.h"
using std::string;

Identifier::Identifier() : Node() {}

Identifier::Identifier(string t, string v) : Node(t, v) {}

std::optional<string> Identifier::execute()
{
    return this->getValue();
}
