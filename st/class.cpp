#include "class.h"

Class::Class() : Variable() {}

Class::Class(string id, string type) : Variable(id, type) {}

void Class::addMethod(Method method)
{
    auto iterator = this->methods.find(method.getId());
    if (iterator == this->methods.end()) // does not exist
    {
        this->methods.insert({method.getId(), method});
    }
    else
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

