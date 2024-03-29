#ifndef CFG_IR_ALLOC_H
#define CFG_IR_ALLOC_H

#include "tac.h"

namespace cfg {

/*
 * @brief: Create a new object of type "A", store it in "x".
 * Example: x  = new A
 * TAC:     x := new TYPE
 *          |     |    |
 *       result   op  lhs
 */
class IRAlloc : public Tac {
public:
    IRAlloc() = delete;
    IRAlloc(std::string lhs, std::string result);
    ~IRAlloc() override = default;

    [[nodiscard]] std::string printInfo() const final;
    [[nodiscard]] std::string printBC() const final;
};

}  // namespace cfg

#endif
