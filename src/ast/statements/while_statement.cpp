#include "ast/statements/while_statement.h"
using ast::WhileStatement;
using std::string;

WhileStatement::WhileStatement() : Statement() {}
WhileStatement::WhileStatement(string t, string v) : Statement(std::move(t), std::move(v)) {}

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
