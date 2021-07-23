#include "type.h"
using std::string;

Type::Type() : Node() {}

Type::Type(string t, string v) : Node(t, v) {}

std::optional<string> Type::generateST()
{
    return this->getValue();
}
