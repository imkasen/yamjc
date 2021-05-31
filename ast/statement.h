#ifndef STATEMENT_H
#define STATEMENT_H

#include "node.h"

class Statement : public Node
{
public:
    Statement();
    Statement(string t, string v);
};

#endif