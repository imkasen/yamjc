#ifndef CFG_BASIC_BLOCK_H
#define CFG_BASIC_BLOCK_H

#include <list>
#include <memory>
#include <string>
#include "tac.h"

namespace cfg {

/*
 * @brief:
 *   Contains sequence of TAC.
 */
class BasicBlock {
private:
    inline static std::size_t id = 0;     // unique id to generate different block name
    std::string name;                     // unique name
    std::weak_ptr<BasicBlock> true_exit;  // use weak_ptr to prevent memory leak, e.g. in "WhileStatement".
    std::shared_ptr<BasicBlock> false_exit;
    std::list<std::shared_ptr<Tac>> tac_instructions;

public:
    BasicBlock();
    virtual ~BasicBlock() = default;

    void setTrueExit(const std::shared_ptr<BasicBlock> &basic_block);
    void setFalseExit(const std::shared_ptr<BasicBlock> &basic_block);
    void addInstruction(const std::shared_ptr<Tac> &instruction);

    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::shared_ptr<BasicBlock> getTrueExit() const;
    [[nodiscard]] std::shared_ptr<BasicBlock> getFalseExit() const;
    [[nodiscard]] std::list<std::shared_ptr<Tac>> getInstructions() const;

    [[nodiscard]] std::string printInfo() const;
    [[nodiscard]] std::string printBC() const;
};

}  // namespace cfg

#endif
