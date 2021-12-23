#include "ast/type.h"
using std::string;

Type::Type() : Node() {}
Type::Type(string t, string v) : Node(std::move(t), std::move(v)) {}

std::optional<string> Type::generateST() {
    // Has value && no children
    if (!this->getValue().empty() && this->children.empty()) {
        return this->getValue();
    }
    // No value && has one "Identifier" child
    else if (this->getValue().empty() && this->children.size() == 1) {
        return this->children.at(0)->generateST().value_or("Unknown");
    }

    return std::nullopt;
}

std::optional<std::string> Type::checkSemantics() {
    // "Type" -> "Identifier"
    if (this->children.size() == 1 && this->getValue().empty()) {
        return this->children.at(0)->checkSemantics();
    }
    // "Type:int", "Type:boolean", "Type:int[]"
    else if (this->children.empty() && !this->getValue().empty()) {
        return this->getValue();
    }

    return std::nullopt;
}
