#include "ast/identifier.h"
using ast::Identifier;
using std::string;

[[maybe_unused]] Identifier::Identifier(string t, string v) : Node(std::move(t), std::move(v)) {}

std::optional<string> Identifier::generateST() {
    return this->getValue();
}

std::optional<string> Identifier::checkSemantics() {
    return this->getValue();
}

IRReturnVal Identifier::generateIR() {
    return this->getValue();
}
