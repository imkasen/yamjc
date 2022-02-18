#ifndef CFG_EXPRESSION_H
#define CFG_EXPRESSION_H

#include "tac.h"

namespace cfg {

/*
 *  Example: x  = y  + z
 *  TAC:     x := y op z
 *          /     |  |  \
 *      result   lhs op  rhs
 */
class Expression : public Tac {
public:
    Expression();
    Expression(std::string op, std::string lhs, std::string rhs, std::string result);
    ~Expression() override = default;
};

}  // namespace cfg

#endif
