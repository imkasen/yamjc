#include "variable_declaration.h"
using std::string;

VarDeclaration::VarDeclaration() : Node() {}

VarDeclaration::VarDeclaration(string t, string v) : Node(t, v) {}
/*
 * 1.
 * Create records in the current "Class" scope.
 * Scope add:
 *     Variable: <name>
 *
 * 2.
 * Get the "Class" record in the "Program" scope.
 * Add variables into "Class".
 *
 * @return: std::nullopt
 */
std::optional<string> VarDeclaration::generateST()
{
    // create variable records
    string variable_type, variable_name;
    variable_type = this->children.at(0)->generateST().value_or("Unknown");
    variable_name = this->children.at(1)->generateST().value_or("Unknown");
    std::shared_ptr<Variable> variable_ptr = std::make_shared<Variable>(variable_name, variable_type);
    VarDeclaration::st.addRecord(variable_name, variable_ptr);

    // add variable records into "Class"
    string scope_name = VarDeclaration::st.getScopeTitle();
    auto record_ptr = VarDeclaration::st.getParentScope()->lookupRecord(scope_name).value_or(nullptr); // std::shared_ptr<Record>
    auto class_ptr = std::dynamic_pointer_cast<STClass>(record_ptr);
    class_ptr->addVariable(variable_ptr);

    return std::nullopt;
}
