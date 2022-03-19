#include "variable.h"
using st::Variable;
using std::string;

Variable::Variable(string name, string type)
    : Record(std::move(name), std::move(type), "Variable") {}
Variable::Variable(string name, string type, string record)
    : Record(std::move(name), std::move(type), std::move(record)) {}

std::unordered_map<std::string, std::shared_ptr<Variable>> Variable::getVariables() const {
    return this->variables;
}

void Variable::addVariable(const std::shared_ptr<Variable> &variable) {
    const auto &[itr, ret] = this->variables.emplace(variable->getName(), variable);
    if (!ret) {  // false
        std::cerr << "The variable " << variable->getName() << " already exists!" << std::endl;
    }
}

/*
 * @return std::shared_ptr<Variable> | std::nullopt
 */
std::optional<std::shared_ptr<Variable>> Variable::lookupVariable(const string &name) const {
    // iterator: std::unordered_map<string, std::shared_ptr<Variable>>::iterator
    auto iterator = this->variables.find(name);
    if (iterator != this->variables.end()) {  // exists
        return iterator->second;
    } else {
        return std::nullopt;
    }
}
