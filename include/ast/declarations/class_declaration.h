#ifndef CLASS_DECLARATION_H
#define CLASS_DECLARATION_H

#include "declarations.h"

class ClassDeclaration : public Declarations {
public:
    ClassDeclaration();
    ClassDeclaration(std::string t, std::string v);
    ~ClassDeclaration() override = default;

    std::optional<std::string> generateST() final;
    std::optional<std::string> checkSemantics() final;
};

#endif