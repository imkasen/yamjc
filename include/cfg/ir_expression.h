#ifndef CFG_IR_EXPRESSION_H
#define CFG_IR_EXPRESSION_H

#include "tac.h"

/*
 *  Example: x  = y  + z
 *  TAC:     x := y op z
 *           /    |  |  \
 *      result   lhs op rhs
 */
class IRExpression : public Tac {
public:
    IRExpression();
    IRExpression(std::string op, std::string lhs, std::string rhs, std::string result);
    ~IRExpression() override = default;
};

#endif
