#include "activation.h"
using smi::Activation;
using std::string;

Activation::Activation(const std::istream::pos_type &npc) {
    this->pc = npc;
    this->local_variables = {};
}

void Activation::addLocalVar(const string &str, const DataTypes &dt) {
    this->local_variables.insert_or_assign(str, dt);
}

std::optional<DataTypes> Activation::getLocalVar(const string &str) {
    auto itr = this->local_variables.find(str);
    if (itr != this->local_variables.end()) {
        return itr->second;
    }
    return std::nullopt;
}

void Activation::setPC(const std::istream::pos_type &npc) {
    this->pc = npc;
}

std::istream::pos_type Activation::getPC() const {
    return this->pc;
}
