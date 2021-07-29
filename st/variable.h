#ifndef VARIABLE_H
#define VARIABLE_H

#include "record.h"
#include <map>
#include <optional>
#include <utility>

class Variable : public Record
{
protected:
    std::map<std::string, std::shared_ptr<Variable>> variables;

public:
    Variable();
    Variable(std::string name, std::string type);
    Variable(std::string name, std::string type, std::string record);

    void addVariable(const std::shared_ptr<Variable> &variable);
    std::optional<std::shared_ptr<Variable>> lookupVariable(const std::string &name) const;

};

#endif