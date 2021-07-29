#ifndef VARIABLE_DECLARATION_H
#define VARIABLE_DECLARATION_H

#include "node.h"

class VarDeclaration : public Node
{
public:
    VarDeclaration();
    VarDeclaration(std::string t, std::string v);

    std::optional<std::string> generateST() override;
};

#endif