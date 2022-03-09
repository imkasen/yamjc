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
    if (type != "int" && type != "boolean") {  // boolean can be turned into int during the back end stage
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
 *      Add an instruction "IRArgument".
 *      Add an instruction "IRMethodCall".
 * @return: std::nullopt
 */
std::optional<IRReturnVal> PrintStatement::generateIR() {
    // 1.
    std::shared_ptr<cfg::BasicBlock> cur_bb = PrintStatement::bb_list.back();
    // 2.
    string tmp_name;
    char type = 0;
    const auto vrt = this->children.at(0)->generateIR().value_or(std::monostate{});
    if (auto s_ptr = std::get_if<string>(&vrt)) {
        tmp_name = *s_ptr;
    }
    const auto &record_ptr = PrintStatement::st.lookupRecord(tmp_name).value_or(nullptr);
    if (record_ptr && record_ptr->getType() == "int") {
        type = 'i';
    } else if (record_ptr && record_ptr->getType() == "boolean") {
        type = 'b';
    } else if (record_ptr && record_ptr->getType() == "int[]") {
        type = 'a';
    } else if (record_ptr) {
        type = 'r';
    }
    std::shared_ptr<cfg::Tac> arg_ptr = std::make_shared<cfg::IRArgument>(tmp_name, type);
    std::shared_ptr<cfg::Tac> call_ptr =
        std::make_shared<cfg::IRMethodCall>("__PRINT__", "1", cfg::Tac::generateTmpVarName('v'));
    cur_bb->addInstruction(arg_ptr);
    cur_bb->addInstruction(call_ptr);
    return std::nullopt;
}
