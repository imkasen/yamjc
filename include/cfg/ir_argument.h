#ifndef CFG_IR_PARAMETER_H
#define CFG_IR_PARAMETER_H

#include "tac.h"

namespace cfg {

/*
 * @brief: Push argument "y" to the stack.
 * Example: x = this.f(y)
 * TAC:         argument y
 *                |    |
 *               op    lhs
 */
class IRArgument : public Tac {
public:
    IRArgument();
    explicit IRArgument(std::string lhs);
    ~IRArgument() override = default;

    [[nodiscard]] std::string printInfo() const final;
    [[nodiscard]] std::string printBC() const final;
};

}  // namespace cfg

#endif
