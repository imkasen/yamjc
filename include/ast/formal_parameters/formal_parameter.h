#ifndef MINI_JAVA_COMPILER_FORMAL_PARAMETER_H
#define MINI_JAVA_COMPILER_FORMAL_PARAMETER_H

#include "formal_parameter_list.h"

class FormalParameter : public FormalParameterList {
public:
    FormalParameter();
    FormalParameter(std::string t, std::string v);
    ~FormalParameter() override = default;

    std::optional<std::string> generateST() final;
};

#endif
