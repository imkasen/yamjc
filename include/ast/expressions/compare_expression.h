#ifndef AST_EXPRESSIONS_COMPARE_EXPRESSION_H
#define AST_EXPRESSIONS_COMPARE_EXPRESSION_H

#include "cfg/ir_expression.h"
#include "expression.h"

namespace ast {

class CompareExpression : public Expression {
public:
    CompareExpression() = delete;
    [[maybe_unused]] CompareExpression(std::string t, std::string v);
    ~CompareExpression() override = default;

    std::optional<std::string> checkSemantics() final;
    std::optional<IRReturnVal> generateIR() final;
};

}  // namespace ast

#endif
