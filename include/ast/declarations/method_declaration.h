#ifndef METHOD_DECLARATION_H
#define METHOD_DECLARATION_H

#include "declarations.h"

class MethodDeclaration : public Declarations {
public:
    MethodDeclaration();
    MethodDeclaration(std::string t, std::string v);
    ~MethodDeclaration() override = default;

    std::optional<std::string> generateST() override;
    std::optional<std::string> checkSemantics() override;
};

#endif