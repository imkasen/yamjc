#ifndef AST_PRIMARY_EXPRESSIONS_PRIMARY_EXPRESSION_H
#define AST_PRIMARY_EXPRESSIONS_PRIMARY_EXPRESSION_H

#include "ast/node.h"

namespace ast {

class PrimaryExpression : public Node {
public:
    PrimaryExpression();
    PrimaryExpression(std::string t, std::string v);
    ~PrimaryExpression() override = default;

    std::optional<std::string> generateST() final;
    std::optional<std::string> checkSemantics() override;
    std::optional<IRReturnVal> generateIR() override;
};

}  // namespace ast

#endif
