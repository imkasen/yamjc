#ifndef AST_DECLARATIONS_VARIABLE_DECLARATION_H
#define AST_DECLARATIONS_VARIABLE_DECLARATION_H

#include "ast/node.h"
#include "cfg/ir_copy.h"

namespace ast {

class VarDeclaration : public Node {
public:
    VarDeclaration();
    VarDeclaration(std::string t, std::string v);
    ~VarDeclaration() override = default;

    std::optional<std::string> generateST() final;
    std::optional<std::string> checkSemantics() final;
    std::optional<IRReturnVal> generateIR() final;
};

}  // namespace ast

#endif