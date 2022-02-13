#include "ast/statements/array_assign_statement.h"
using std::string;

/*
        "ArrayAssignStatement:[]="
         /           |           \
    "Identifier" "Expression"   "Expression"
 */

ArrayAssignStatement::ArrayAssignStatement() : Statement() {}
ArrayAssignStatement::ArrayAssignStatement(string t, string v) : Statement(std::move(t), std::move(v)) {}

/*
 * @brief: Compare types of lhs and rhs.
 * @return: std::nullopt
 */
std::optional<string> ArrayAssignStatement::checkSemantics() {
    // e.g. number[0] = 20;
    string lhs_name = this->children.at(0)->checkSemantics().value_or("");  // "Identifier"
    string pos_type = this->children.at(1)->checkSemantics().value_or("");
    string rhs_type = this->children.at(2)->checkSemantics().value_or("");

    auto record_ptr = Statement::st.lookupRecord(lhs_name).value_or(nullptr);
    if (record_ptr) {
        if (pos_type != "int") {
            string msg =
                R"([Semantic Analysis] - Error: only "int" can be used to access array's position in scope ")" +
                ArrayAssignStatement::st.getScopeTitle() + "\"!";
            ArrayAssignStatement::printErrMsg(msg);
        }
        string lhs_record_type = record_ptr->getType();
        if (lhs_record_type != "int[]" || rhs_type != "int") {
            string msg = "[Semantic Analysis] - Error: Can not assign \"" + rhs_type + "\" (rhs) to \"" +
                         lhs_record_type + "\" (lhs) in the scope \"" + Statement::st.getScopeTitle() + "\"!";
            ArrayAssignStatement::printErrMsg(msg);
        }
    } else {
        string msg = "[Semantic Analysis] - Error: Variable \"" + lhs_name + "\" does not exist in scope \"" +
                     ArrayAssignStatement::st.getScopeTitle() + "\"!";
        ArrayAssignStatement::printErrMsg(msg);
    }

    return std::nullopt;
}
