#ifndef CFG_COPY_H
#define CFG_COPY_H

#include "tac.h"

namespace cfg {

/*
 *  Example: x  = y
 *  TAC    : x := y
 *           |    |
 *         result lhs
 */
class Copy : public Tac {
public:
    Copy();
    Copy(std::string lhs, std::string result);
    ~Copy() override = default;
};

}  // namespace cfg

#endif
