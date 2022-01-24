#ifndef VARIABLE_DECLARATION_H
#define VARIABLE_DECLARATION_H

#include "ast/node.h"

class VarDeclaration : public Node {
public:
    VarDeclaration();
    VarDeclaration(std::string t, std::string v);

    std::optional<std::string> generateST() override;
    std::optional<std::string> checkSemantics() override;
};

#endif