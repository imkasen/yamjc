#ifndef CFG_BASIC_BLOCK_H
#define CFG_BASIC_BLOCK_H

#include <list>
#include <memory>
#include <string>
#include "tac.h"

namespace cfg {

/*
 * @brief:
 *   1. "true_exit == nullptr": no true exit
 *   2. "true_exit": single exit arrow
 */
class BasicBlock {
private:
    std::string name;  // unique name
    std::list<Tac> tac_instructions;
    std::shared_ptr<Tac> condition;
    std::shared_ptr<BasicBlock> true_exit;
    std::shared_ptr<BasicBlock> false_exit;
public:
    BasicBlock();
    virtual ~BasicBlock() = default;
};

}  // namespace cfg

#endif
