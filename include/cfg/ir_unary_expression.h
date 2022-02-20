#ifndef CFG_IR_UNARY_EXPRESSION_H
#define CFG_IR_UNARY_EXPRESSION_H

#include "tac.h"

namespace cfg {

/*
 * @brief: Calculate "op y", store the result in "x".
 * Example: x  =  ! y
 * TAC    : x := op y
 *         /      |  \
 *      result   op   lhs
 */
class IRUnaryExpression : public Tac {
public:
    IRUnaryExpression();
    IRUnaryExpression(std::string op, std::string lhs, std::string result);
    ~IRUnaryExpression() override = default;
};

}  // namespace cfg

#endif
