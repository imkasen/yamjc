#ifndef VARIABLE_H
#define VARIABLE_H

#include "record.h"

#include <unordered_map>
using std::unordered_map;

class Variable : public Record
{
private:
    string record = "variable";

protected:
    unordered_map<string, Variable> variables;

public:
    Variable();
    Variable(string id, string type);

    void addVariable(Variable variable);
    Variable lookupVariable(string name);
};

#endif