#ifndef AST_METHOD_BODY_H
#define AST_METHOD_BODY_H

#include "node.h"

namespace ast {

class MethodBody : public Node {
public:
    MethodBody() = delete;
    [[maybe_unused]] MethodBody(std::string t, std::string v);
    ~MethodBody() override = default;

    std::optional<std::string> generateST() final;
    std::optional<std::string> checkSemantics() final;
    std::optional<IRReturnVal> generateIR() final;
};

}  // namespace ast

#endif
