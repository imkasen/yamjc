#ifndef MINI_JAVA_COMPILER_FORMAL_PARAMETER_H
#define MINI_JAVA_COMPILER_FORMAL_PARAMETER_H

#include "ast/node.h"

class FormalParameter : public Node {
public:
    FormalParameter();
    FormalParameter(std::string t, std::string v);
    ~FormalParameter() override = default;

    std::optional<std::string> generateST() override;
};

#endif
