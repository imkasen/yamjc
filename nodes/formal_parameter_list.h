#ifndef FORMAL_PARAMETER_LIST_H
#define FORMAL_PARAMETER_LIST_H

#include "node.h"

class FormalParameterList : public Node
{
    public:
        FormalParameterList();
        FormalParameterList(string t, string v);
};

#endif