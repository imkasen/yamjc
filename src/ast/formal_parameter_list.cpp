#include "ast/formal_parameter_list.h"
using std::string;
using std::size_t;

FormalParameterList::FormalParameterList() : Node() {}
FormalParameterList::FormalParameterList(string t, string v) : Node(std::move(t), std::move(v)) {}

/*
 * 1.
 * Create records in the current "Method" scope.
 * Scope add:
 *     Variable <name>
 *
 * 2.
 * Get the "Method" record in the "Class" scope.
 * Add methods into "Method".
 *
 * @return: std::nullopt
 */
std::optional<string> FormalParameterList::generateST()
{
    for (size_t i = 0; i < this->children.size(); i += 2)
    {
        // create parameter records
        string parameter_type = this->children.at(i)->generateST().value_or("Unknown");
        string parameter_name = this->children.at(i + 1)->generateST().value_or("Unknown");
        std::shared_ptr<Parameter> parameter_ptr = std::make_shared<Parameter>(parameter_name, parameter_type);
        FormalParameterList::st.addRecord(parameter_name, parameter_ptr);

        // add parameter records into "Method"
        string scope_name = FormalParameterList::st.getScopeTitle();
        string scope_type = FormalParameterList::st.getScopeType();
        auto record_ptr = FormalParameterList::st.lookupRecord(scope_name).value_or(nullptr);
        if (scope_type == "Method" && record_ptr)
        {
            auto method_ptr = std::dynamic_pointer_cast<Method>(record_ptr);
            method_ptr->addParameter(parameter_ptr);
        }
    }

    return std::nullopt;
}
