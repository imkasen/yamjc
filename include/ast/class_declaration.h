#ifndef CLASS_DECLARATION_H
#define CLASS_DECLARATION_H

#include "node.h"

class ClassDeclaration : public Node
{
public:
    ClassDeclaration();
    ClassDeclaration(std::string t, std::string v);

    std::optional<std::string> generateST() override;
    std::optional<std::string> checkSemantics() override;
};

#endif