#include "ast/statements/while_statement.h"
using ast::WhileStatement;
using std::string;

[[maybe_unused]] WhileStatement::WhileStatement(string t, string v) : Statement(std::move(t), std::move(v)) {}

/*
 *  Node: "WhileStatement"
 *  @brief: Same like "IfStatement"
 */
std::optional<string> WhileStatement::checkSemantics() {
    string type = this->children.at(0)->checkSemantics().value_or("");
    if (type != "boolean") {
        string msg = R"([Semantic Analysis] - Error: WHILE condition should be "boolean" in scope ")" +
                     Statement::st.getScopeTitle() + "\"!";
        Statement::printErrMsg(msg);
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
 *   3. Create a rejoinder "BasicBlock"
 *   4. Add an instruction "IRCondJump" into boolean condition "BasicBlock"
 * @return: block_ptr
 */
IRReturnVal WhileStatement::generateIR() {
    // 1.
    std::shared_ptr<cfg::BasicBlock> bl_bb_ptr = WhileStatement::createBB();
    WhileStatement::bb_list.push_back(bl_bb_ptr);
    const auto tmp_vrt = this->children.at(0)->generateIR();
    std::string cdi_tmp_name, label_name;
    if (auto s_ptr = std::get_if<string>(&tmp_vrt)) {
        cdi_tmp_name = *s_ptr;
    }
    // 2.
    std::shared_ptr<cfg::BasicBlock> true_bb_ptr = WhileStatement::createBB();
    WhileStatement::bb_list.push_back(true_bb_ptr);
    bl_bb_ptr->setTrueExit(true_bb_ptr);
    this->children.at(1)->generateIR();
    WhileStatement::bb_list.back()->setTrueExit(bl_bb_ptr);
    WhileStatement::bb_list.back()->addInstruction(std::make_shared<cfg::IRJump>(bl_bb_ptr->getName()));
    // 3.
    std::shared_ptr<cfg::BasicBlock> rej_ptr = WhileStatement::createBB();
    WhileStatement::bb_list.push_back(rej_ptr);
    bl_bb_ptr->setFalseExit(rej_ptr);
    // 4.
    label_name = rej_ptr->getName();
    std::shared_ptr<cfg::Tac> cdi_jmp_ins = std::make_shared<cfg::IRCondJump>(cdi_tmp_name, label_name);
    bl_bb_ptr->addInstruction(cdi_jmp_ins);

    return bl_bb_ptr;
}
