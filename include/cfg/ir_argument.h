#ifndef CFG_IR_ARGUMENT_H
#define CFG_IR_ARGUMENT_H

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
private:
    char para_type;  // i-int, b-boolean, a-int[], r-self-defined class
public:
    IRArgument();
    IRArgument(std::string lhs, char t);
    ~IRArgument() override = default;

    [[nodiscard]] std::string printInfo() const final;
    [[nodiscard]] std::string printBC() const final;
};

}  // namespace cfg

#endif
