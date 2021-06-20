#ifndef VARIABLE_H
#define VARIABLE_H

#include "record.h"
#include <map>
#include <optional>

class Variable : public Record
{
private:
    inline static const std::string RECORD = "variable";

protected:
    std::map<std::string, Variable> variables;

public:
    Variable();
    Variable(std::string id, std::string type);

    void addVariable(Variable variable);
    std::optional<Variable> lookupVariable(std::string name) const;
};

#endif