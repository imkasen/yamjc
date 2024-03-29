#ifndef CFG_IR_ARRAY_ALLOC_H
#define CFG_IR_ARRAY_ALLOC_H

#include "tac.h"

namespace cfg {

/*
 * @brief: Create a new object of type "int[]", with size "N", store in "x".
 * Example: x  = new int[N]
 *          default lhs = "int[]"
 *                    |
 * TAC:     x := new TYPE, N
 *          |     |        |
 *        result  op      rhs
 */
class IRArrayAlloc : public Tac {
public:
    IRArrayAlloc() = delete;
    IRArrayAlloc(std::string rhs, std::string result);
    ~IRArrayAlloc() override = default;

    [[nodiscard]] std::string printInfo() const final;
    [[nodiscard]] std::string printBC() const final;
};

}  // namespace cfg

#endif
