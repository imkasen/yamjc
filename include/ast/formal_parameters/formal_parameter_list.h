#ifndef FORMAL_PARAMETER_LIST_H
#define FORMAL_PARAMETER_LIST_H

#include "ast/node.h"

class FormalParameterList : public Node {
public:
    FormalParameterList();
    FormalParameterList(std::string t, std::string v);
    ~FormalParameterList() override = default;

    std::optional<std::string> generateST() override;
};

#endif