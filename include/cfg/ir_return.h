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
private:
    char para_type;  // i-int, b-boolean, a-int[], r-self-defined class
public:
    IRReturn() = delete;
    IRReturn(std::string lhs, char t);
    ~IRReturn() override = default;

    [[nodiscard]] std::string printInfo() const final;
    [[nodiscard]] std::string printBC() const final;
};

}  // namespace cfg

#endif
