#ifndef METHOD_DECLARATION_H
#define METHOD_DECLARATION_H

#include "node.h"

class MethodDeclaration : public Node
{
public:
    MethodDeclaration();
    MethodDeclaration(std::string t, std::string v);
};

#endif