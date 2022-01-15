#include "ast/return.h"
using std::string;

Return::Return() : Node() {}
Return::Return(string t, string v) : Node(std::move(t), std::move(v)) {}

/*
 * @brief: Check if the return value type matches the class declaration.
 * @return: std::nullopt
 */
std::optional<string> Return::checkSemantics() {
    string return_type = this->children.at(0)->checkSemantics().value_or("");
    string method_name = Return::st.getScopeTitle();
    auto record_ptr = Return::st.lookupRecord(method_name).value_or(nullptr);
    if (record_ptr) {
        string record_ptr_type = record_ptr->getType();
        if (record_ptr_type != return_type) {
            string msg = "[Semantic Analysis] - Error: return type \"" + return_type +
                         "\" does not match the declaration (\"" + record_ptr_type + "\")!";
            Return::printErrMsg(msg);
        }
    } else {
        string msg = "[Semantic Analysis] - Error: Can not find \"" + method_name + "\"!";
        Return::printErrMsg(msg);
    }

    return std::nullopt;
}
