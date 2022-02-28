#include "ast/primary_expressions/alloc_expression.h"
using ast::AllocExpression;
using st::Record;
using std::string;

/*
 *   "AllocExpression:new"
 *             |
 *        "Identifier"
 */

AllocExpression::AllocExpression() : PrimaryExpression() {}
AllocExpression::AllocExpression(string t, string v) : PrimaryExpression(std::move(t), std::move(v)) {}

/*
 * @return: std::nullopt | string
 */
std::optional<string> AllocExpression::checkSemantics() {
    string class_name = this->children.at(0)->checkSemantics().value_or("");
    std::shared_ptr<Record> c_record_ptr = AllocExpression::st.lookupRecordInRoot(class_name).value_or(nullptr);
    if (c_record_ptr && c_record_ptr->getRecord() == "Class") {
        return c_record_ptr->getType();
    } else {
        string msg = "[Semantic Analysis] - Error: Class \"" + class_name + "\" does not exist!";
        AllocExpression::printErrMsg(msg);
    }

    return std::nullopt;
}

/*
 * @brief:
 *   1. Obtain the current "BasicBlock".
 *   2. Get the return value of lhs, create an instruction "IRAlloc"
 * @return: string
 */
std::optional<IRReturnVal> AllocExpression::generateIR() {
    // 1.
    std::shared_ptr<cfg::BasicBlock> cur_bb = AllocExpression::bb_list.back();
    // 2.
    string lhs, tmp_name;
    const auto lhs_vrt = this->children.at(0)->generateIR().value_or(std::monostate{});
    if (auto s_ptr = std::get_if<string>(&lhs_vrt)) {
        lhs = *s_ptr;
    }
    tmp_name = cfg::Tac::generateTmpVarName();
    std::shared_ptr<cfg::Tac> instruction = std::make_shared<cfg::IRAlloc>(lhs, tmp_name);
    cur_bb->addInstruction(instruction);

    return tmp_name;
}
