#include "ast/formal_parameter_list.h"
using std::size_t;
using std::string;

FormalParameterList::FormalParameterList() : Node() {}
FormalParameterList::FormalParameterList(string t, string v) : Node(std::move(t), std::move(v)) {}

/*
 * @brief:
 *   1. Create "Parameter" records in the current "Method" scope.
 *      Add into the current scope:
 *          Variable: <parameter name>
 *   2. Get the "Method" ptr in the "Class" scope.
 *      Add "Parameter" ptr into "Method" ptr.
 * @return: std::nullopt
 */
std::optional<string> FormalParameterList::generateST() {
    for (size_t i = 0; i < this->children.size(); i += 2) {
        // 1.
        string parameter_type = this->children.at(i)->generateST().value_or("Unknown");
        string parameter_name = this->children.at(i + 1)->generateST().value_or("Unknown");
        std::shared_ptr<Parameter> parameter_ptr = std::make_shared<Parameter>(parameter_name, parameter_type);
        FormalParameterList::st.addRecord(parameter_name, parameter_ptr);

        // 2.
        string scope_name = FormalParameterList::st.getScopeTitle();
        string scope_type = FormalParameterList::st.getScopeType();
        auto record_ptr = FormalParameterList::st.lookupRecord(scope_name).value_or(nullptr);
        if (scope_type == "Method" && record_ptr) {
            auto method_ptr = std::dynamic_pointer_cast<Method>(record_ptr);
            method_ptr->addParameter(parameter_ptr);
        }
    }

    return std::nullopt;
}
