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
