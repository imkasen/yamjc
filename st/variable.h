#ifndef VARIABLE_H
#define VARIABLE_H

#include "record.h"

#include <map>
using std::map;

class Variable : public Record
{
private:
    string record = "variable";

protected:
    map<string, Variable> variables;

public:
    Variable();
    Variable(string id, string type);

    void addVariable(Variable variable);
    Variable lookupVariable(string name);
};

#endif