#ifndef CFG_IR_METHOD_CALL_H
#define CFG_IR_METHOD_CALL_H

#include "tac.h"

namespace cfg {

/*
 * @brief: Call function "f", use "N" params from the stack.
 * Example: x  = this.f(y)
 * TAC:     x := call f, N
 *         /      |   |   \
 *      result   op  lhs  rhs
 */
class IRMethodCall : public Tac {
public:
    IRMethodCall();
    IRMethodCall(std::string lhs, std::string rhs, std::string result);
    ~IRMethodCall() override = default;

    [[nodiscard]] std::string printInfo() const final;
    [[nodiscard]] std::string printBC() const final;
};

}  // namespace cfg

#endif
