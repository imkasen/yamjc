#ifndef AST_RETURN_H
#define AST_RETURN_H

#include "cfg/ir_return.h"
#include "node.h"

namespace ast {

class Return : public Node {
public:
    Return() = delete;
    [[maybe_unused]] Return(std::string t, std::string v);
    ~Return() override = default;

    std::optional<std::string> generateST() final;
    std::optional<std::string> checkSemantics() final;
    IRReturnVal generateIR() final;
};

}  // namespace ast

#endif
