 #ifndef CFG_IR_RETURN_H
#define CFG_IR_RETURN_H

#include "tac.h"

namespace cfg {

/*
 * @brief: Return y
 * Example: return y
 * TAC:     return y
 *           |     |
 *          op     lhs
 */
class IRReturn : public Tac {
public:
    IRReturn();
    explicit IRReturn(std::string lhs);
    ~IRReturn() override = default;

    [[nodiscard]] std::string printInfo() const final;
};

}  // namespace cfg

#endif
