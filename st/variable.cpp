#include "variable.h"

Variable::Variable() : Record() {}

Variable::Variable(string id, string type) : Record(id, type) {}

void Variable::addVariable(Variable variable)
{
    auto iterator = this->variables.find(variable.getId());
    if (iterator == this->variables.end()) // does not exist
    {
        this->variables.insert({variable.getId(), variable});
    }
    else 
    {
        std::cerr << "The variable " << variable.getId() << " already exists!" << endl;
    }
}

Variable Variable::lookupVariable(string name)
{
    auto iterator = this->variables.find(name);
    if (iterator != this->variables.end()) // exists
    {
        return iterator->second;
    }
}