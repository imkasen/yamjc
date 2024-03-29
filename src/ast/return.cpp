#include "ast/return.h"
using ast::Return;
using std::string;

[[maybe_unused]] Return::Return(string t, string v) : Node(std::move(t), std::move(v)) {}

/*
 * @brief: It will not be called at all, do nothing.
 * @return: std::nullopt
 */
std::optional<string> Return::generateST() {
    return std::nullopt;
}

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

/*
 * @brief:
 *   1. Get the current "BasicBlock"
 *   2. Create an instruction "IRReturn"
 * @return: std::monostate
 */
IRReturnVal Return::generateIR() {
    string lhs;
    char type = 0;
    std::shared_ptr<cfg::BasicBlock> cur_bb = Return::bb_list.back();
    const auto vrt = this->children.at(0)->generateIR();
    if (auto ptr = std::get_if<string>(&vrt)) {
        lhs = *ptr;
    }
    const auto record_ptr = Return::st.lookupRecord(lhs).value_or(nullptr);
    if (record_ptr && record_ptr->getType() == "int") {
        type = 'i';
    } else if (record_ptr && record_ptr->getType() == "boolean") {
        type = 'b';
    } else if (record_ptr && record_ptr->getType() == "int[]") {
        type = 'a';
    } else if (record_ptr) {
        type = 'r';
    }
    cur_bb->addInstruction(std::make_shared<cfg::IRReturn>(lhs, type));

    return std::monostate {};
}
