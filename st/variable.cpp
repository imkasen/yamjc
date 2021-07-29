#include "variable.h"
using std::string;

Variable::Variable() : Record() {}
Variable::Variable(string name, string type) : Record(name, type, "Variable") {}
Variable::Variable(string name, string type, string record) : Record(name, type, record) {}

void Variable::addVariable(const std::shared_ptr<Variable> &variable)
{
    // ret: std::pair<std::map<string, std::shared_ptr<Variable>>::iterator, bool>
    auto ret = this->variables.insert({variable->getName(), variable}); // = insert(std::pair<string, std::shared_ptr<Variable>>(variable->getId(), variable))
    if (!ret.second) // false
    {
        std::cerr << "The variable " << variable->getName() << " already exists!" << std::endl;
    }
}

/*
 * @return std::shared_ptr<Variable> | std::nullopt
 */
std::optional<std::shared_ptr<Variable>> Variable::lookupVariable(const string &name) const
{
    // iterator: std::map<string, std::shared_ptr<Variable>>::iterator
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
