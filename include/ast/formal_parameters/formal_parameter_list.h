#ifndef AST_FORMAL_PARAMETERS_FORMAL_PARAMETER_LIST_H
#define AST_FORMAL_PARAMETERS_FORMAL_PARAMETER_LIST_H

#include "ast/node.h"

namespace ast {

class FormalParameterList : public Node {
public:
    FormalParameterList() = delete;
    FormalParameterList(std::string t, std::string v);
    ~FormalParameterList() override = default;

    std::optional<std::string> generateST() override;
    std::optional<std::string> checkSemantics() final;
    IRReturnVal generateIR() override;
};

}  // namespace ast

#endif