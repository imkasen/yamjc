#ifndef AST_FORMAL_PARAMETERS_FORMAL_PARAMETER_H
#define AST_FORMAL_PARAMETERS_FORMAL_PARAMETER_H

#include "cfg/ir_assign.h"
#include "formal_parameter_list.h"

namespace ast {

class FormalParameter : public FormalParameterList {
public:
    FormalParameter();
    FormalParameter(std::string t, std::string v);
    ~FormalParameter() override = default;

    std::optional<std::string> generateST() final;
    std::optional<IRReturnVal> generateIR() final;
};

}  // namespace ast

#endif
