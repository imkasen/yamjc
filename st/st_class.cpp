#include "st_class.h"
using std::string;

STClass::STClass() : Variable() {}

STClass::STClass(string id, string type) : Variable(id, type) {}

void STClass::addMethod(Method method)
{
    auto ret = this->methods.insert(std::pair<string, Method>(method.getId(), method));
    if (!ret.second && ret.first->first == method.getId()) // false
    {
        std::cerr << "The method " << method.getId() << " already exists!" << std::endl;
    }
}

std::optional<Method> STClass::lookupMethod(string name) const
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

