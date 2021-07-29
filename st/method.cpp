#include "method.h"
using std::string;

Method::Method() : Variable() {}
Method::Method(string name, string type) : Variable(name, type, "Method") {}

void Method::addParameter(const std::shared_ptr<Variable> &parameter)
{
    auto ret = this->parameters.insert({parameter->getName(), parameter});
    if (!ret.second) // false
    {
        std::cerr << "The parameter " << parameter->getName() << " already exists in the method!" << std::endl;
    }
}

/*
 * @return std::shared_ptr<Variable> | std::nullopt
 */
std::optional<std::shared_ptr<Variable>> Method::lookupParameter(const string &name) const
{
    auto iterator = this->parameters.find(name);
    if (iterator != this->parameters.end()) // exists
    {
        return iterator->second;
    }
    else
    {
        return std::nullopt;
    }
}
