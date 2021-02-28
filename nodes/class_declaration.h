#ifndef CLASS_DECLARATION_H
#define CLASS_DECLARATION_H

#include "node.h"

class ClassDeclaration : public Node
{
    public:
        ClassDeclaration();
        ClassDeclaration(string t, string v);
};

#endif