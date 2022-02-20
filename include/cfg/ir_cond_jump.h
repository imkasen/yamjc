#ifndef CFG_IR_COND_JUMP_H
#define CFG_IR_COND_JUMP_H

#include "tac.h"

namespace cfg {

/*
 * @brief: If "x" is false, next execute the instruction labeled "L".
 * TAC: if false x goto L
 *              /   |   |
 *            lhs  op  rhs
 */
class IRCondJump : public Tac {
public:
    IRCondJump();
    IRCondJump(std::string lhs, std::string rhs);
    ~IRCondJump() override = default;
};

}

#endif
