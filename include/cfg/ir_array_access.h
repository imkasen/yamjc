#ifndef CFG_IR_ARRAY_ACCESS_H
#define CFG_IR_ARRAY_ACCESS_H

#include "tac.h"

namespace cfg {

/*
 * @brief: Copy "y[i]" to "x"; Copy "x" to "y[i]".
 * Example: x  = y[i]    or    y[i]  = x
 * TAC:     x := y[i]          y[i] := x
 *          |      |            |      |
 *       result   lhs         result  lhs
 */
class IRArrayAccess : public Tac {
public:
    IRArrayAccess();
    IRArrayAccess(std::string lhs, std::string result);
    ~IRArrayAccess() override = default;

    [[nodiscard]] std::string printInfo() const;
};

}  // namespace cfg

#endif
