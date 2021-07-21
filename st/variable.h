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
    std::map<std::string, std::shared_ptr<Variable>> variables;

public:
    Variable();
    Variable(std::string id, std::string type);

    void addVariable(const std::shared_ptr<Variable> &variable);
    std::optional<std::shared_ptr<Variable>> lookupVariable(const std::string &name) const;

};

#endif