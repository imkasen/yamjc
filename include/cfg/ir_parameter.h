#ifndef CFG_IR_PARAMETER_H
#define CFG_IR_PARAMETER_H

#include "tac.h"

namespace cfg {

/*
 * @brief: Push parameter "y" to the stack.
 * Example: f(y)
 * TAC:     argument y
 *             |     |
 *             op    lhs
 */
class IRParameter : public Tac {
private:
    char para_type; // i-int, b-boolean, a-int[], r-self-defined class
public:
    IRParameter() = delete;
    IRParameter(std::string lhs, char t);
    ~IRParameter() override = default;

    [[nodiscard]] std::string printInfo() const final;
    [[nodiscard]] std::string printBC() const final;
};

}  // namespace cfg

#endif
