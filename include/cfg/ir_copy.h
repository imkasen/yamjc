#ifndef CFG_IR_COPY_H
#define CFG_IR_COPY_H

#include "tac.h"

namespace cfg {

/*
 * @brief: Copy "y" to "x".
 * Example: x  = y
 * TAC    : x := y
 *          |    |
 *        result lhs
 */
class IRCopy : public Tac {
public:
    IRCopy();
    IRCopy(std::string lhs, std::string result);
    ~IRCopy() override = default;
};

}  // namespace cfg

#endif
