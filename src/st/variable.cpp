#include "st/variable.h"
using std::string;

Variable::Variable() : Record() {}
Variable::Variable(string name, string type)
    : Record(std::move(name), std::move(type), "Variable") {}
Variable::Variable(string name, string type, string record)
    : Record(std::move(name), std::move(type), std::move(record)) {}

std::unordered_map<std::string, std::shared_ptr<Variable>> Variable::getVariables() const
{
    return this->variables;
}

void Variable::addVariable(const std::shared_ptr<Variable> &variable)
{
    // ret: std::pair<std::unordered_map<string, std::shared_ptr<Variable>>::iterator, bool>
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
    // iterator: std::unordered_map<string, std::shared_ptr<Variable>>::iterator
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
