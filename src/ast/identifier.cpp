#include "ast/identifier.h"
using std::string;

Identifier::Identifier() : Node() {}
Identifier::Identifier(string t, string v) : Node(std::move(t), std::move(v)) {}

std::optional<string> Identifier::generateST() {
    return this->getValue();
}

std::optional<std::string> Identifier::checkSemantics() {
    return this->getValue();
}
