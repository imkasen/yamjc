#ifndef AST_DECLARATIONS_METHOD_DECLARATION_H
#define AST_DECLARATIONS_METHOD_DECLARATION_H

#include "ast/node.h"

namespace ast {

class MethodDeclaration : public Node {
public:
    MethodDeclaration() = delete;
    [[maybe_unused]] MethodDeclaration(std::string t, std::string v);
    ~MethodDeclaration() override = default;

    std::optional<std::string> generateST() final;
    std::optional<std::string> checkSemantics() final;
    std::optional<IRReturnVal> generateIR() final;
};

}  // namespace ast

#endif