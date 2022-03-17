#include "ast/statements/assign_statement.h"
using ast::AssignStatement;
using std::string;

/*
       "AssignStatement:="
           /         \
     "Identifier" "Expression"
 */

AssignStatement::AssignStatement(string t, string v) : Statement(std::move(t), std::move(v)) {}

/*
 * @brief: Compare types of lhs and rhs.
 * @return: std::nullopt
 */
std::optional<string> AssignStatement::checkSemantics() {
    // e.g. xxx = 123;
    //      xxx = NEW ...;
    // etc...
    string lhs_name = this->children.at(0)->checkSemantics().value_or("");  // "Identifier"
    string rhs_type = this->children.at(1)->checkSemantics().value_or("");  // "Expression"

    auto record_ptr = AssignStatement::st.lookupRecord(lhs_name).value_or(nullptr);
    if (record_ptr) {
        string lhs_record_type = record_ptr->getType();
        // lhs and rhs are different types,
        // "Class" extends from "Class".
        if (lhs_record_type != rhs_type && rhs_type.find(lhs_record_type) == string::npos) {
            string msg = "[Semantic Analysis] - Error: Can not assign \"" + rhs_type + "\" (rhs) to \"" +
                         lhs_record_type + "\" (lhs) in the scope \"" + AssignStatement::st.getScopeTitle() + "\"!";
            AssignStatement::printErrMsg(msg);
        }
    } else {
        string msg = "[Semantic Analysis] - Error: Variable \"" + lhs_name + "\" does not exist in scope \"" +
                     AssignStatement::st.getScopeTitle() + "\"!";
        AssignStatement::printErrMsg(msg);
    }

    return std::nullopt;
}

/*
 * @brief:
 *   1. Obtain current "BasicBlock"
 *   2. Create an instruction "IRAssign"
 * @return: std::nullopt
 */
std::optional<IRReturnVal> AssignStatement::generateIR() {
    // 1.
    std::shared_ptr<cfg::BasicBlock> cur_bb = AssignStatement::bb_list.back();
    // 2.
    string result, lhs;
    char type = 0;
    const auto r_vrt = this->children.at(0)->generateIR().value_or(std::monostate{});
    if (auto s_ptr = std::get_if<string>(&r_vrt)) {
        result = *s_ptr;
    }
    const auto lhs_vrt = this->children.at(1)->generateIR().value_or(std::monostate{});
    if (auto s_ptr = std::get_if<string>(&lhs_vrt)) {
        lhs = *s_ptr;
    }
    const auto &record_ptr = AssignStatement::st.lookupRecord(lhs).value_or(nullptr);
    if (record_ptr && record_ptr->getType() == "int") {
        type = 'i';
    } else if (record_ptr && record_ptr->getType() == "boolean") {
        type = 'b';
    } else if (record_ptr && record_ptr->getType() == "int[]") {
        type = 'a';
    } else if (record_ptr) {
        type = 'r';
    }
    std::shared_ptr<cfg::Tac> instruction = std::make_shared<cfg::IRAssign>(lhs, result, type);
    cur_bb->addInstruction(instruction);

    return std::nullopt;
}
