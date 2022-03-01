#ifndef CFG_IR_ARRAY_ACCESS_H
#define CFG_IR_ARRAY_ACCESS_H

#include "tac.h"

namespace cfg {

/*
 * @brief: Copy "y[i]" to "x".
 * Example: x  = y[i]
 * TAC:     x := y[i]
 *          |    |  \
 *       result lhs rhs
 */
class IRArrayAccess : public Tac {
public:
    IRArrayAccess();
    IRArrayAccess(std::string lhs, std::string rhs, std::string result);
    ~IRArrayAccess() override = default;

    [[nodiscard]] std::string printInfo() const final;
};

}  // namespace cfg

#endif
