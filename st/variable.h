#ifndef VARIABLE_H
#define VARIABLE_H

#include "record.h"
#include <map>
#include <optional>
#include <utility>

class Variable : public Record
{
private:
    inline static const std::string RECORD = "variable";

protected:
    std::map<std::string, Variable> variables;

public:
    Variable();
    Variable(std::string id, std::string type);

    void addVariable(const Variable &variable);
    std::optional<Variable> lookupVariable(const std::string &name) const;

    virtual ~Variable() = default;
};

#endif