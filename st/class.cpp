#include "class.h"

Class::Class() : Variable() {}

Class::Class(string id, string type) : Variable(id, type) {}

void Class::addMethod(Method method)
{
    auto ret = this->methods.insert(std::pair<string, Method>(method.getId(), method));
    if (!ret.second && ret.first->first == method.getId()) // false
    {
        std::cerr << "The method " << method.getId() << " already exists!" << endl;
    }
}

Method Class::lookupMethod(string name)
{
    auto iterator = this->methods.find(name);
    if (iterator != this->methods.end()) // exists
    {
        return iterator->second;
    }
}

