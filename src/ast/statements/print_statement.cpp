#include "ast/statements/print_statement.h"
using ast::PrintStatement;
using std::string;

PrintStatement::PrintStatement() : Statement() {}
PrintStatement::PrintStatement(string t, string v) : Statement(std::move(t), std::move(v)) {}

/*
 * Node: "PrintStatement: System.out.println"
 *   Traverse child nodes, and check the return value.
 *   The grammar restricts that only integers can be print,
 *   so the return value must be "int".
 * @return: std::nullopt
 */
std::optional<string> PrintStatement::checkSemantics() {
    string type = this->children.at(0)->checkSemantics().value_or("");
    if (type != "int") {
        string msg = R"([Semantic Analysis] - Error: only "int" can be print in scope ")" +
                     PrintStatement::st.getScopeTitle() + "\"!";
        PrintStatement::printErrMsg(msg);
    }
    return std::nullopt;
}

/*
 * @brief:
 *   1. Obtain current BasicBlock.
 *   2. Traverse the child node, obtain the return value.
 *      Add an instruction "IRParameter".
 *      Add an instruction "IRMethodCall".
 * @return: std::nullopt
 */
std::optional<IRReturnVal> PrintStatement::generateIR() {
    // 1.
    std::shared_ptr<cfg::BasicBlock> cur_bb = PrintStatement::cfg_list.back();
    // 2.
    const auto vrt = this->children.at(0)->generateIR().value_or(std::monostate{});
    if (auto s_ptr = std::get_if<string>(&vrt)) {
        string tmp_name = *s_ptr;
        std::shared_ptr<cfg::Tac> param_ptr = std::make_shared<cfg::IRParameter>(tmp_name);
        std::shared_ptr<cfg::Tac> call_ptr =
            std::make_shared<cfg::IRMethodCall>("PRINTLN", "1", cfg::Tac::generateTmpVarName());
        cur_bb->addInstruction(param_ptr);
        cur_bb->addInstruction(call_ptr);
    }
    return std::nullopt;
}
