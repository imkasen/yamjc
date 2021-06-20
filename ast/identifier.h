#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "node.h"

class Identifier : public Node
{
public:
    Identifier();
    Identifier(string t, string v);
};

#endif
