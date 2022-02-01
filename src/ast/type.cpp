#include "ast/type.h"
using std::string;

Type::Type() : Node() {}
Type::Type(string t, string v) : Node(std::move(t), std::move(v)) {}

/*
 * @return: std::nullopt || string
 */
std::optional<string> Type::generateST() {
    // Has value && no children
    if (!this->getValue().empty() && this->children.empty()) {
        return this->getValue();
    }
    // No value && has one "Identifier" child
    // User-defined type
    else if (this->getValue().empty() && this->children.size() == 1) {
        return this->children.at(0)->generateST().value_or("Unknown");
    }

    return std::nullopt;
}

/*
 * @brief:
 *   1.    "Type"
 *           |
 *      "Identifier"
 *   2. "Type:int" or "Type:boolean" or "Type:int[]"
 * @return: std::nullopt || string
 */
std::optional<string> Type::checkSemantics() {
    // 1.
    if (this->children.size() == 1 && this->getValue().empty()) {
        return this->children.at(0)->checkSemantics();
    }
    // 2.
    else if (this->children.empty() && !this->getValue().empty()) {
        return this->getValue();
    }

    return std::nullopt;
}
