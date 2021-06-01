#include "method.h"

Method::Method() : Variable() {}

Method::Method(string id, string type) : Variable(id, type) {}

void Method::addParameter(Variable parameter)
{
    auto iterator = this->parameters.find(parameter.getId());
    if (iterator == this->parameters.end()) // does not exist
    {
        this->parameters.insert({parameter.getId(), parameter});
    }
    else
    {
        std::cerr << "The parameter" << parameter.getId() << " already exists!" << endl;
    }
}

Variable Method::lookupParameter(string name)
{
    auto iterator = this->parameters.find(name);
    if (iterator != this->parameters.end()) // exists
    {
        return iterator->second;
    }
}
