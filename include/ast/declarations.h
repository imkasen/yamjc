#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include "node.h"

class Declarations : public Node {
public:
    Declarations();
    Declarations(std::string t, std::string v);
};

#endif
