#ifndef CLASS_H
#define CLASS_H

#include "method.h"

class Class : public Variable
{
private:
    string record = "class";

protected:
    std::map<string, Method> methods;

public:
    Class();
    Class(string id, string type);

    void addMethod(Method method);
    Method lookupMethod(string name);
};

#endif