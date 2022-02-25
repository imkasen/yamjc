#ifndef CFG_IR_COND_JUMP_H
#define CFG_IR_COND_JUMP_H

#include "tac.h"

namespace cfg {

/*
 * @brief: Conditional jump, if "x" is false, next execute the instruction labeled "L".
 * TAC: if false x goto L
 *              /   |   |
 *            lhs  op  result(label)
 */
class IRCondJump : public Tac {
public:
    IRCondJump();
    IRCondJump(std::string lhs, std::string label);
    ~IRCondJump() override = default;
};

}

#endif