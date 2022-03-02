#include "ast/identifier.h"
using ast::Identifier;
using std::string;

Identifier::Identifier() : Node() {}
Identifier::Identifier(string t, string v) : Node(std::move(t), std::move(v)) {}

std::optional<string> Identifier::generateST() {
    return this->getValue();
}

std::optional<string> Identifier::checkSemantics() {
    return this->getValue();
}

/*
 * @brief:
 *   Get the node value and search it in the records of Symbol Table,
 *   if the record exists, and record's "Value" != "", return record->value
 *   else return node->value
 * @return IRReturnVal
 */
std::optional<IRReturnVal> Identifier::generateIR() {
    string node_value = this->getValue();
    if (auto ptr = Identifier::st.lookupRecord(node_value).value_or(nullptr)) {
        if (!ptr->getValue().empty()) {
            return ptr->getValue();
        }
    }
    return node_value;
}
