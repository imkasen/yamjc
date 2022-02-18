#ifndef CFG_UNARY_EXPRESSION_H
#define CFG_UNARY_EXPRESSION_H

#include "tac.h"

namespace cfg {

/*
 *  Example: x  =  ! y
 *  TAC    : x := op y
 *          /      |  \
 *       result   op   lhs
 */
class UnaryExpression : public Tac {
public:
    UnaryExpression();
    UnaryExpression(std::string op, std::string lhs, std::string result);
    ~UnaryExpression() override = default;
};

}  // namespace cfg

#endif
