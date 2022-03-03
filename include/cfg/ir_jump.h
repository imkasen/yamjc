#ifndef CFG_IR_JUMP_H
#define CFG_IR_JUMP_H

#include "tac.h"

namespace cfg {

/*
 * @brief: Unconditional jump, next execute the instruction labeled "L".
 * TAC: goto L
 *       |    \
 *       op  result(label)
 */
class IRJump : public Tac {
public:
    IRJump();
    explicit IRJump(std::string label);
    ~IRJump() override = default;

    [[nodiscard]] std::string printInfo() const final;
    [[nodiscard]] std::string printBC() const final;
};

}  // namespace cfg

#endif
