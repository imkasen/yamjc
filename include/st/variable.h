#ifndef ST_VARIABLE_H
#define ST_VARIABLE_H

#include <optional>
#include <unordered_map>
#include "record.h"

namespace st {

// local variables in "Class" and "Method"
class Variable : public Record {
private:
    std::unordered_map<std::string, std::shared_ptr<Variable>> variables;

public:
    Variable();
    Variable(std::string name, std::string type);
    Variable(std::string name, std::string type, std::string record);
    ~Variable() override = default;

    std::unordered_map<std::string, std::shared_ptr<Variable>> getVariables() const;

    void addVariable(const std::shared_ptr<Variable> &variable);
    std::optional<std::shared_ptr<Variable>> lookupVariable(const std::string &name) const;
};

}  // namespace st

#endif