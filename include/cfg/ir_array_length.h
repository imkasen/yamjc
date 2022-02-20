#ifndef CFG_IR_ARRAY_LENGTH_H
#define CFG_IR_ARRAY_LENGTH_H

#include "tac.h"

namespace cfg {

/*
 * @brief: Get the member length of "y", store the result in "x".
 * Example: x  = y.length
 * TAC:     x := length y
 *          |      |    |
 *        result   op  lhs
 */
class IRArrayLength : public Tac {
public:
    IRArrayLength();
    IRArrayLength(std::string lhs, std::string result);
    ~IRArrayLength() override = default;
};

}  // namespace cfg

#endif
