#ifndef VARIABLE_H
#define VARIABLE_H

#include "record.h"

#include <map>

class Variable : public Record
{
private:
    string record = "variable";

protected:
    std::map<string, Variable> variables;

public:
    Variable();
    Variable(string id, string type);

    void addVariable(Variable variable);
    Variable lookupVariable(string name);
};

#endif