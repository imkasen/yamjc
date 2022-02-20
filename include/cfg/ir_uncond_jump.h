#ifndef CFG_IR_UNCOND_JUMP_H
#define CFG_IR_UNCOND_JUMP_H

#include "tac.h"

namespace cfg {

/*
 * @brief: Next execute the instruction labeled "L".
 * TAC: goto L
 *       |   |
 *       op  lhs
 */
class IRUncondJump : public Tac {
public:
    IRUncondJump();
    explicit IRUncondJump(std::string lhs);
    ~IRUncondJump() override = default;
};

}  // namespace cfg

#endif
