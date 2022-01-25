#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include "ast/node.h"

class Declarations : public Node {
public:
    Declarations();
    Declarations(std::string t, std::string v);
    ~Declarations() override = default;
};

#endif
