#ifndef VARIABLE_H
#define VARIABLE_H

#include "record.h"
#include <map>
#include <optional>
using std::optional;
using std::nullopt;

class Variable : public Record
{
private:
    inline static const string RECORD = "variable";

protected:
    std::map<string, Variable> variables;

public:
    Variable();
    Variable(string id, string type);

    void addVariable(Variable variable);
    optional<Variable> lookupVariable(string name) const;
};

#endif