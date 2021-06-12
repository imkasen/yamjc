#include "method.h"

Method::Method() : Variable() {}

Method::Method(string id, string type) : Variable(id, type) {}

void Method::addParameter(Variable parameter)
{
    auto ret = this->parameters.insert(std::pair<string, Variable>(parameter.getId(), parameter));
    if (!ret.second && ret.first->first == parameter.getId()) // false
    {
        std::cerr << "The parameter " << parameter.getId() << " already exists!" << endl;
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
