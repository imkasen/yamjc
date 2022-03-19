#ifndef AST_DECLARATIONS_CLASS_DECLARATION_H
#define AST_DECLARATIONS_CLASS_DECLARATION_H

#include "ast/node.h"

namespace ast {

class ClassDeclaration : public Node {
public:
    ClassDeclaration() = delete;
    [[maybe_unused]] ClassDeclaration(std::string t, std::string v);
    ~ClassDeclaration() override = default;

    std::optional<std::string> generateST() final;
    std::optional<std::string> checkSemantics() final;
    std::optional<IRReturnVal> generateIR() final;
};

}  // namespace ast

#endif