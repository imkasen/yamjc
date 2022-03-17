#ifndef AST_TYPE_H
#define AST_TYPE_H

#include "node.h"

namespace ast {

class Type : public Node {
public:
    Type() = delete;
    Type(std::string t, std::string v);
    ~Type() override = default;

    std::optional<std::string> generateST() final;
    std::optional<std::string> checkSemantics() final;
    std::optional<IRReturnVal> generateIR() final;
};

}  // namespace ast

#endif