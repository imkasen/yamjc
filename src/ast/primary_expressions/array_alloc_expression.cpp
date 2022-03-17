#include "ast/primary_expressions/array_alloc_expression.h"
using ast::ArrayAllocExpression;
using std::string;

/*
   "ArrayAllocExpression"
          |
      "Expression"
 */

ArrayAllocExpression::ArrayAllocExpression(string t, string v) : PrimaryExpression(std::move(t), std::move(v)) {}

/*
 * @return: string
 */
std::optional<string> ArrayAllocExpression::checkSemantics() {
    string type = this->children.at(0)->checkSemantics().value_or("");
    if (type != "int") {
        string msg = R"([Semantic Analysis] - Error: Array size should be "int" in scope ")" +
                     ArrayAllocExpression::st.getScopeType() + "\"!";
        ArrayAllocExpression::printErrMsg(msg);
    }

    return "int[]";
}

/*
 * @brief:
 *   1. Get current "BasicBlock"
 *   2. Create an instruction "IRArrayAlloc"
 * @return: IRReturnVal
 */
std::optional<IRReturnVal> ArrayAllocExpression::generateIR() {
    // 1.
    std::shared_ptr<cfg::BasicBlock> cur_bb = ArrayAllocExpression::bb_list.back();
    // 2.
    string tmp_name, n = "0";
    const auto vrt = this->children.at(0)->generateIR().value_or(std::monostate{});
    if (auto s_ptr = std::get_if<string>(&vrt)) {
        n = *s_ptr;
    }
    tmp_name = cfg::Tac::generateTmpVarName('a');
    std::shared_ptr<cfg::Tac> instruction = std::make_shared<cfg::IRArrayAlloc>(n, tmp_name);
    cur_bb->addInstruction(instruction);

    return tmp_name;
}
