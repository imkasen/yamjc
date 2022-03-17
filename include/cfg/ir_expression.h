#ifndef CFG_IR_EXPRESSION_H
#define CFG_IR_EXPRESSION_H

#include "tac.h"

namespace cfg {

/*
 * @brief: Calculate "y op z", store the result in "x".
 * Example: x  = y  + z
 * TAC:     x := y op z
 *         /     |  |  \
 *     result   lhs op  rhs
 */
class IRExpression : public Tac {
public:
    IRExpression() = delete;
    IRExpression(std::string op, std::string lhs, std::string rhs, std::string result);
    ~IRExpression() override = default;

    [[nodiscard]] std::string printInfo() const final;
    [[nodiscard]] std::string printBC() const final;
};

}  // namespace cfg

#endif
