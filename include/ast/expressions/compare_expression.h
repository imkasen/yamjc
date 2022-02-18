#ifndef AST_EXPRESSIONS_COMPARE_EXPRESSION_H
#define AST_EXPRESSIONS_COMPARE_EXPRESSION_H

#include "expression.h"

namespace ast {

class CompareExpression : public Expression {
public:
    CompareExpression();
    CompareExpression(std::string t, std::string v);
    ~CompareExpression() override = default;

    std::optional<std::string> checkSemantics() final;
};

}  // namespace ast

#endif
