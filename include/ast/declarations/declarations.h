#ifndef AST_DECLARATIONS_DECLARATIONS_H
#define AST_DECLARATIONS_DECLARATIONS_H

#include "ast/node.h"

class Declarations : public Node {
public:
    Declarations();
    Declarations(std::string t, std::string v);
    ~Declarations() override = default;
};

#endif
