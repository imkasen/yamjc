#ifndef AST_DECLARATIONS_METHOD_DECLARATION_H
#define AST_DECLARATIONS_METHOD_DECLARATION_H

#include "declarations.h"

namespace ast {

class MethodDeclaration : public Declarations {
public:
    MethodDeclaration();
    MethodDeclaration(std::string t, std::string v);
    ~MethodDeclaration() override = default;

    std::optional<std::string> generateST() final;
    std::optional<std::string> checkSemantics() final;
    std::optional<IRReturnVal> generateIR() final;
};

}  // namespace ast

#endif