#ifndef CLASS_H
#define CLASS_H

#include "record.h"
#include "variable.h"
#include "method.h"

class Class : public Record
{
private:
    string record = "class";

protected:
    map<string, Variable> variables;
    map<string, Method> methods;

public:
    Class();
    Class(map<string, Variable> variables, map<string, Method> methods);

    void addVariable();
    void addMethod();
    Variable lookupVariable();
    Method lookupMethod();
};

#endif