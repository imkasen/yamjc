#ifndef SMI_ACTIVATION_STK_H
#define SMI_ACTIVATION_STK_H

#include <memory>
#include <stack>
#include "activation.h"

namespace smi {

class ActivationStk {
private:
    std::stack<std::shared_ptr<Activation>> stk;

public:
    ActivationStk() = default;
    ~ActivationStk() = default;

    void push(const std::shared_ptr<Activation> &act_ptr);

    [[nodiscard]] std::size_t size() const;
    [[nodiscard]] std::optional<std::shared_ptr<Activation>> top() const;
    void pop();
};

}  // namespace smi

#endif
