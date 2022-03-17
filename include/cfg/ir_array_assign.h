#ifndef CFG_IR_ARRAY_ASSIGN_H
#define CFG_IR_ARRAY_ASSIGN_H

#include "tac.h"

namespace cfg {

/*
 * @brief: Copy "x" to "y[i]".
 * Example: y[i]  = x
 * TAC:     y[i] := x
 *         /  |     |
 *      lhs  rhs  result
 */
class IRArrayAssign : public Tac {
public:
    IRArrayAssign() = delete;
    IRArrayAssign(std::string lhs, std::string rhs, std::string result);
    ~IRArrayAssign() override = default;

    [[nodiscard]] std::string printInfo() const final;
    [[nodiscard]] std::string printBC() const final;
};

}  // namespace cfg

#endif
