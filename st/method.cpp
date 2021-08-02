#include "method.h"
using std::string;

Method::Method() : Parameter() {}
Method::Method(string name, string type) : Parameter(name, type, "Method") {}

const std::map<std::string, std::shared_ptr<Parameter>> Method::getParameters() const
{
    return this->parameters;
}

void Method::addParameter(const std::shared_ptr<Parameter> &parameter)
{
    auto ret = this->parameters.insert({parameter->getName(), parameter});
    if (!ret.second) // false
    {
        std::cerr << "The parameter " << parameter->getName() << " already exists in the method!" << std::endl;
    }
}

/*
 * @return std::shared_ptr<Parameter> | std::nullopt
 */
std::optional<std::shared_ptr<Parameter>> Method::lookupParameter(const string &name) const
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
