#include "ast/statements/if_statement.h"
using std::string;

/*
                       "IfStatement"
               /              |             \
     "CompareExpression"  "Statement"  ["ElseStatement"]
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
