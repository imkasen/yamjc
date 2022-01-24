#ifndef FORMAL_PARAMETER_LIST_H
#define FORMAL_PARAMETER_LIST_H

#include "ast/node.h"

class FormalParameterList : public Node {
public:
    FormalParameterList();
    FormalParameterList(std::string t, std::string v);

    std::optional<std::string> generateST() override;
};

#endif