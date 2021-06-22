#include "variable.h"
using std::string;

Variable::Variable() : Record() {}

Variable::Variable(string id, string type) : Record(id, type) {}

void Variable::addVariable(const Variable &variable)
{
    // ret: std::pair<std::map<string, Variable>::iterator, bool>
    auto ret = this->variables.insert({variable.getId(), variable}); // = insert(std::pair<string, Variable>(variable.getId(), variable))
    if (!ret.second) // false
    {
        std::cerr << "The variable " << variable.getId() << " already exists!" << std::endl;
    }
}

/*
 * @return Variable | std::nullopt
 */
std::optional<Variable> Variable::lookupVariable(const string &name) const
{
    // iterator: std::map<string, Variable>::iterator
    auto iterator = this->variables.find(name);
    if (iterator != this->variables.end()) // exists
    {
        return iterator->second;
    }
    else
    {
        return std::nullopt;
    }
}
