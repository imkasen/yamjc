#include "st_class.h"
using std::string;

STClass::STClass() : Variable() {}

STClass::STClass(string name, string type) : Variable(name, type) {}

void STClass::addMethod(const std::shared_ptr<Method> &method)
{
    auto ret = this->methods.insert({method->getName(), method});
    if (!ret.second) // false
    {
        std::cerr << "The method " << method->getName() << " already exists in the class!" << std::endl;
    }
}

/*
 * @return std::shared_ptr<Method> | std::nullopt
 */
std::optional<std::shared_ptr<Method>> STClass::lookupMethod(const string &name) const
{
    auto iterator = this->methods.find(name);
    if (iterator != this->methods.end()) // exists
    {
        return iterator->second;
    }
    else
    {
        return std::nullopt;
    }
}

