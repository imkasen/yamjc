#ifndef CFG_IR_ASSIGN_H
#define CFG_IR_ASSIGN_H

#include "tac.h"

namespace cfg {

/*
 * @brief: Assign "y" to "x".
 * Example: x  = y
 * TAC    : x := y
 *          |    |
 *        result lhs
 */
class IRAssign : public Tac {
private:
    char para_type;  // y, i-int, b-boolean, a-int[], r-self-defined class
public:
    IRAssign();
    IRAssign(std::string lhs, std::string result, char t);
    ~IRAssign() override = default;

    [[nodiscard]] std::string printInfo() const final;
    [[nodiscard]] std::string printBC() const final;
};

}  // namespace cfg

#endif
