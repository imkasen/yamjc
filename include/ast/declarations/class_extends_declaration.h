#ifndef AST_DECLARATIONS_CLASS_EXTENDS_DECLARATION_H
#define AST_DECLARATIONS_CLASS_EXTENDS_DECLARATION_H

#include "declarations.h"

class ClassExtendsDeclaration : public Declarations {
public:
    ClassExtendsDeclaration();
    ClassExtendsDeclaration(std::string t, std::string v);
    ~ClassExtendsDeclaration() override = default;

    std::optional<std::string> generateST() final;
    std::optional<std::string> checkSemantics() final;
};

#endif
