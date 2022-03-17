#ifndef AST_DECLARATIONS_DECLARATIONS_H
#define AST_DECLARATIONS_DECLARATIONS_H

#include "ast/node.h"

namespace ast {

class Declarations : public Node {
public:
    Declarations() = delete;
    Declarations(std::string t, std::string v);
    ~Declarations() override = default;

    std::optional<IRReturnVal> generateIR() final;
};

}  // namespace ast

#endif
