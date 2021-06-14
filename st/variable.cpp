#include "variable.h"

Variable::Variable() : Record() {}

Variable::Variable(string id, string type) : Record(id, type) {}

void Variable::addVariable(Variable variable)
{
    // ret: std::pair<std::map<string, Variable>::iterator, bool>
    auto ret = this->variables.insert(std::pair<string, Variable>(variable.getId(), variable));
    if (!ret.second && ret.first->first == variable.getId()) // false
    {
        std::cerr << "The variable " << variable.getId() << " already exists!" << endl;
    }
}

Variable Variable::lookupVariable(string name)
{
    // iterator: std::map<string, Variable>::iterator
    auto iterator = this->variables.find(name);
    if (iterator != this->variables.end()) // exists
    {
        return iterator->second;
    }
}