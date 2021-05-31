#ifndef TYPE_H
#define TYPE_H

#include "node.h"

class Type : public Node
{
public:
    Type();
    Type(string t, string v);
};

#endif