#ifndef AST_DECLARATIONS_DECLARATIONS_H
#define AST_DECLARATIONS_DECLARATIONS_H

#include "ast/node.h"

namespace ast {

class Declarations : public Node {
public:
    Declarations() = delete;
    [[maybe_unused]] Declarations(std::string t, std::string v);
    ~Declarations() override = default;

    std::optional<std::string> generateST() final;
    std::optional<std::string> checkSemantics() final;
    IRReturnVal generateIR() final;
};

}  // namespace ast

#endif
