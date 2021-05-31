#ifndef VARIABLE_DECLARATION_H
#define VARIABLE_DECLARATION_H

#include "node.h"

class VarDeclaration : public Node
{
public:
    VarDeclaration();
    VarDeclaration(string t, string v);
};

#endif