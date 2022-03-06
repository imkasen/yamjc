#ifndef SMI_ACTIVATION_STK_H
#define SMI_ACTIVATION_STK_H

#include <stack>
#include "activation.h"

namespace smi {

class ActivationStk {
private:
    std::stack<Activation> stk;

public:
    ActivationStk() = default;
    ~ActivationStk() = default;

    void emplace(const std::istream::pos_type &npc);
    void push(const Activation &act);

    [[nodiscard]] std::size_t size() const;
    [[nodiscard]] std::optional<Activation> top() const;
    std::optional<Activation> pop();
};

}  // namespace smi

#endif
