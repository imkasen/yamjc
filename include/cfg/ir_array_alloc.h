#ifndef CFG_IR_ARRAY_ALLOC_H
#define CFG_IR_ARRAY_ALLOC_H

#include "tac.h"

namespace cfg {

/*
 * @brief: Create a new object of type "int[]", with size "N", store in "x".
 * Example: x  = new int[N]
 * TAC:     x := new TYPE, N
 *          |     |   |    |
 *        result  op lhs  rhs
 */
class IRArrayAlloc : public Tac {
public:
    IRArrayAlloc();
    IRArrayAlloc(std::string lhs, std::string rhs, std::string result);
    ~IRArrayAlloc() override = default;

    [[nodiscard]] std::string printInfo() const;
};

}  // namespace cfg

#endif
