#ifndef CFG_IR_PARAMETER_H
#define CFG_IR_PARAMETER_H

#include "tac.h"

namespace cfg {

/*
 * @brief: Push param "y" to the stack.
 * Example: x = this.f(y)
 * TAC:          param y
 *                |    |
 *               op    lhs
 */
class IRParameter : public Tac {
public:
    IRParameter();
    explicit IRParameter(std::string lhs);
    ~IRParameter() override = default;

    [[nodiscard]] std::string printInfo() const final;
    [[nodiscard]] std::string printBC() const final;
};

}  // namespace cfg

#endif
