#ifndef AST_RETURN_H
#define AST_RETURN_H

#include "node.h"
#include "cfg/ir_return.h"

namespace ast {

class Return : public Node {
public:
    Return();
    Return(std::string t, std::string v);
    ~Return() override = default;

    std::optional<std::string> generateST() final;
    std::optional<std::string> checkSemantics() final;
    std::optional<IRReturnVal> generateIR() final;
};

}  // namespace ast

#endif
