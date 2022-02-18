#ifndef AST_FORMAL_PARAMETERS_FORMAL_PARAMETER_H
#define AST_FORMAL_PARAMETERS_FORMAL_PARAMETER_H

#include "formal_parameter_list.h"

namespace ast {

class FormalParameter : public FormalParameterList {
public:
    FormalParameter();
    FormalParameter(std::string t, std::string v);
    ~FormalParameter() override = default;

    std::optional<std::string> generateST() final;
};

}  // namespace ast

#endif
