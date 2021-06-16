#ifndef ST_CLASS_H
#define ST_CLASS_H

#include "method.h"

class STClass : public Variable
{
private:
    string record = "class";
    std::map<string, Method> methods;

public:
    STClass();
    STClass(string id, string type);

    void addMethod(Method method);
    optional<Method> lookupMethod(string name);
};

#endif