#include "ast/statements/assign_statement.h"
using std::string;

AssignStatement::AssignStatement() : Statement() {}
AssignStatement::AssignStatement(string t, string v) : Statement(std::move(t), std::move(v)) {}

/*
 *     "AssignStatement:="
 *        /         \
 * "Identifier" "Expression"
 * @brief: Compare types of lhs and rhs.
 * @return: std::nullopt
 */
std::optional<string> AssignStatement::checkSemantics() {
    // e.g. xxx = 123;
    //      xxx = NEW ...;
    // etc...
    if (this->children.size() == 2) {
        string lhs_name = this->children.at(0)->checkSemantics().value_or("");  // "Identifier"
        string rhs_type = this->children.at(1)->checkSemantics().value_or("");  // "Expression"

        auto record_ptr = AssignStatement::st.lookupRecord(lhs_name).value_or(nullptr);
        if (record_ptr) {
            string lhs_record_type = record_ptr->getType();
            // lhs and rhs are different types,
            // "Class" extends from "Class".
            if (lhs_record_type != rhs_type && rhs_type.find(lhs_record_type) == string::npos) {
                string msg = "[Semantic Analysis] - Error: Can not assign \"" + rhs_type + "\" (rhs) to \"" +
                             lhs_record_type + "\" (lhs) in the scope \"" + AssignStatement::st.getScopeTitle() + "\"!";
                AssignStatement::printErrMsg(msg);
            }
        } else {
            string msg = "[Semantic Analysis] - Error: Variable \"" + lhs_name + "\" does not exist in scope \"" +
                         AssignStatement::st.getScopeTitle() + "\"!";
            AssignStatement::printErrMsg(msg);
        }
    }

    return std::nullopt;
}
