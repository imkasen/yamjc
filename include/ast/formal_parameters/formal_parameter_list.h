#ifndef AST_FORMAL_PARAMETERS_FORMAL_PARAMETER_LIST_H
#define AST_FORMAL_PARAMETERS_FORMAL_PARAMETER_LIST_H

#include "ast/node.h"

class FormalParameterList : public Node {
public:
    FormalParameterList();
    FormalParameterList(std::string t, std::string v);
    ~FormalParameterList() override = default;
};

#endif