#include "variable_declaration.h"
using std::string;

VarDeclaration::VarDeclaration() : Node() {}
VarDeclaration::VarDeclaration(string t, string v) : Node(t, v) {}
/*
 * 1.
 * Create records in the current "Class" || "Method" scope.
 * Scope add:
 *     Variable: <name>
 *
 * 2.
 * Get the "Class" || "Method" record in the "Program" || "Class" scope.
 * Add variables into "Class" || "Method".
 *
 * @return: std::nullopt
 */
std::optional<string> VarDeclaration::generateST()
{
    // create variable records
    string variable_type = this->children.at(0)->generateST().value_or("Unknown");
    string variable_name = this->children.at(1)->generateST().value_or("Unknown");
    std::shared_ptr<Variable> variable_ptr = std::make_shared<Variable>(variable_name, variable_type);
    VarDeclaration::st.addRecord(variable_name, variable_ptr);

    // add variable records into "Class" || "Method"
    string scope_name = VarDeclaration::st.getScopeTitle();
    string scope_type = VarDeclaration::st.getScopeType();
    auto record_ptr = VarDeclaration::st.lookupRecord(scope_name).value_or(nullptr); // std::shared_ptr<Record>
    if (scope_type == "Class" && record_ptr)
    {
        auto class_ptr = std::dynamic_pointer_cast<STClass>(record_ptr);
        class_ptr->addVariable(variable_ptr);
    }
    else if (scope_type == "Method" && record_ptr)
    {
        auto method_ptr = std::dynamic_pointer_cast<Method>(record_ptr);
        method_ptr->addVariable(variable_ptr);
    }

    return std::nullopt;
}
