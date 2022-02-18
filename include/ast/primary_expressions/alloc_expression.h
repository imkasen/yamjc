#ifndef AST_PRIMARY_EXPRESSIONS_ALLOC_EXPRESSION_H
#define AST_PRIMARY_EXPRESSIONS_ALLOC_EXPRESSION_H

#include "primary_expression.h"

namespace ast {

class AllocExpression : public PrimaryExpression {
public:
    AllocExpression();
    AllocExpression(std::string t, std::string v);
    ~AllocExpression() override = default;

    std::optional<std::string> checkSemantics() final;
};

}  // namespace ast

#endif
