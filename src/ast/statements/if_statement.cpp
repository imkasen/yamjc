#include "ast/statements/if_statement.h"
using ast::IfStatement;
using std::string;

/*
                       "IfStatement"
               /              |             \
     "CompareExpression"  "Statement"  "ElseStatement"
 */

IfStatement::IfStatement() : Statement() {}
IfStatement::IfStatement(string t, string v) : Statement(std::move(t), std::move(v)) {}

/*
 * @return: std::nullopt
 */
std::optional<string> IfStatement::checkSemantics() {
    string type = this->children.at(0)->checkSemantics().value_or("");
    if (type != "boolean") {
        string msg = R"([Semantic Analysis] - Error: IF condition should be "boolean" in scope ")" +
                     IfStatement::st.getScopeTitle() + "\"!";
        IfStatement::printErrMsg(msg);
    }

    for (std::size_t i = 1; i < this->children.size(); ++i) {
        this->children.at(i)->checkSemantics();
    }

    return std::nullopt;
}

/*
 * @brief:
 *   1. Create a boolean condition "BasicBlock", add into boolean instruction
 *   2. Create a true branch "BasicBlock", add into instruction
 *   3. Create a false branch "BasicBlock", add into instruction
 *   4. Add an instruction "IRCondJump" into boolean condition "BasicBlock"
 *   5. Create a rejoinder "BasicBlock"
 * @return: IRReturnVal
 */
std::optional<IRReturnVal> IfStatement::generateIR() {
    // 1.
    std::shared_ptr<cfg::BasicBlock> bl_bb_ptr = IfStatement::createBB();
    IfStatement::bb_list.push_back(bl_bb_ptr);
    const auto tmp_vrt = this->children.at(0)->generateIR().value_or(std::monostate{});
    std::string cdi_tmp_name, label_name;
    if (auto s_ptr = std::get_if<string>(&tmp_vrt)) {
        cdi_tmp_name = *s_ptr;
    }
    // 2.
    std::shared_ptr<cfg::BasicBlock> true_bb_ptr = IfStatement::createBB();
    IfStatement::bb_list.push_back(true_bb_ptr);
    bl_bb_ptr->setTrueExit(true_bb_ptr);
    this->children.at(1)->generateIR();
    true_bb_ptr = IfStatement::bb_list.back();
    // 3.
    std::shared_ptr<cfg::BasicBlock> false_bb_ptr;
    const auto false_vrt = this->children.at(2)->generateIR().value_or(std::monostate{});
    if (auto ptr = std::get_if<std::shared_ptr<cfg::BasicBlock>>(&false_vrt)) {
        false_bb_ptr = *ptr;
    }
    label_name = false_bb_ptr->getName();
    bl_bb_ptr->setFalseExit(false_bb_ptr);
    false_bb_ptr = IfStatement::bb_list.back();
    // 4.
    std::shared_ptr<cfg::Tac> cdi_jmp_ins = std::make_shared<cfg::IRCondJump>(cdi_tmp_name, label_name);
    bl_bb_ptr->addInstruction(cdi_jmp_ins);
    // 5.
    std::shared_ptr<cfg::BasicBlock> rej_ptr = IfStatement::createBB();
    IfStatement::bb_list.push_back(rej_ptr);
    true_bb_ptr->addInstruction(std::make_shared<cfg::IRJump>(rej_ptr->getName()));
    true_bb_ptr->setTrueExit(rej_ptr);
    false_bb_ptr->setTrueExit(rej_ptr);

    return bl_bb_ptr;
}
