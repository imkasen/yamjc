#ifndef CLASS_EXTENDS_DECLARATION_H
#define CLASS_EXTENDS_DECLARATION_H

#include "ast/node.h"

class ClassExtendsDeclaration : public Node {
public:
    ClassExtendsDeclaration();
    ClassExtendsDeclaration(std::string t, std::string v);
    ~ClassExtendsDeclaration() override = default;
};

#endif
