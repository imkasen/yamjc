#ifndef AST_DECLARATIONS_CLASS_EXTENDS_DECLARATION_H
#define AST_DECLARATIONS_CLASS_EXTENDS_DECLARATION_H

#include "ast/node.h"

namespace ast {

class ClassExtendsDeclaration : public Node {
public:
    ClassExtendsDeclaration() = delete;
    [[maybe_unused]] ClassExtendsDeclaration(std::string t, std::string v);
    ~ClassExtendsDeclaration() override = default;

    std::optional<std::string> generateST() final;
    std::optional<std::string> checkSemantics() final;
    std::optional<IRReturnVal> generateIR() final;
};

}  // namespace ast

#endif
