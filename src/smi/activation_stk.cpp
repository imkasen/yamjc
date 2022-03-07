#include "activation_stk.h"
using smi::ActivationStk;
using smi::Activation;

void ActivationStk::push(const std::shared_ptr<Activation> &act_ptr) {
    this->stk.push(act_ptr);
}

std::size_t ActivationStk::size() const {
    return this->stk.size();
}

std::optional<std::shared_ptr<Activation>> ActivationStk::top() const {
    if (!this->stk.empty()) {
        return this->stk.top();
    }
    return std::nullopt;
}

void ActivationStk::pop() {
    if (!this->stk.empty()) {
        this->stk.pop();
    }
}
