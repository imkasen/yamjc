#include "st/method.h"
using std::string;

Method::Method() : Parameter() {}
Method::Method(string name, string type) : Parameter(std::move(name), std::move(type), "Method") {}

std::deque<std::shared_ptr<Parameter>> Method::getParameters() const
{
    return this->parameters;
}

void Method::addParameter(const std::shared_ptr<Parameter> &parameter)
{
    if (!this->lookupParameter(parameter->getName()).value_or(nullptr))
    {
        this->parameters.push_back(parameter);
    }
}

/*
 * @return std::shared_ptr<Parameter> | std::nullopt
 */
std::optional<std::shared_ptr<Parameter>> Method::lookupParameter(const std::string &name) const
{
    for (const auto &para : this->parameters)
    {
        if (para->getName() == name)
        {
            return para;
        }
    }

    return std::nullopt;
}
