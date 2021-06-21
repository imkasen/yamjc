#include "method.h"
using std::string;

Method::Method() : Variable() {}

Method::Method(string id, string type) : Variable(id, type) {}

void Method::addParameter(const Variable &parameter)
{
    auto ret = this->parameters.insert(std::pair<string, Variable>(parameter.getId(), parameter));
    if (!ret.second && ret.first->first == parameter.getId()) // false
    {
        std::cerr << "The parameter " << parameter.getId() << " already exists!" << std::endl;
    }
}

/*
 * @return Variable | std::nullopt
 */
std::optional<Variable> Method::lookupParameter(const string &name) const
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
