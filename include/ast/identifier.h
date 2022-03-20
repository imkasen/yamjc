#ifndef AST_IDENTIFIER_H
#define AST_IDENTIFIER_H

#include "node.h"

namespace ast {

class Identifier : public Node {
public:
    Identifier() = delete;
    [[maybe_unused]] Identifier(std::string t, std::string v);
    ~Identifier() override = default;

    std::optional<std::string> generateST() final;
    std::optional<std::string> checkSemantics() final;
    IRReturnVal generateIR() final;
};

}  // namespace ast

#endif
