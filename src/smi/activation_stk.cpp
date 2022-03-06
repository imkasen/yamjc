#include "activation_stk.h"
using smi::ActivationStk;
using smi::Activation;

void ActivationStk::emplace(const std::istream::pos_type &npc) {
    this->stk.emplace(npc);
}

void ActivationStk::push(const Activation &act) {
    this->stk.push(act);
}

std::size_t ActivationStk::size() const {
    return this->stk.size();
}

std::optional<Activation> ActivationStk::top() const {
    if (!this->stk.empty()) {
        return this->stk.top();
    }
    return std::nullopt;
}

std::optional<Activation> ActivationStk::pop() {
    if (!this->stk.empty()) {
        const auto &act = this->stk.top();
        this->stk.pop();
        return act;
    }
    return std::nullopt;
}
