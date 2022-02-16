#ifndef AST_DECLARATIONS_VARIABLE_DECLARATION_H
#define AST_DECLARATIONS_VARIABLE_DECLARATION_H

#include "declarations.h"

class VarDeclaration : public Declarations {
public:
    VarDeclaration();
    VarDeclaration(std::string t, std::string v);
    ~VarDeclaration() override = default;

    std::optional<std::string> generateST() final;
    std::optional<std::string> checkSemantics() final;
};

#endif