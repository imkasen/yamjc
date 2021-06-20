#ifndef FORMAL_PARAMETER_LIST_H
#define FORMAL_PARAMETER_LIST_H

#include "node.h"

class FormalParameterList : public Node
{
public:
    FormalParameterList();
    FormalParameterList(std::string t, std::string v);
};

#endif