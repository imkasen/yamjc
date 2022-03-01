#ifndef AST_EXPRESSIONS_ARRAY_ACCESS_EXPRESSION_H
#define AST_EXPRESSIONS_ARRAY_ACCESS_EXPRESSION_H

#include "cfg/ir_array_access.h"
#include "expression.h"

namespace ast {

class ArrayAccessExpression : public Expression {
public:
    ArrayAccessExpression();
    ArrayAccessExpression(std::string t, std::string v);
    ~ArrayAccessExpression() override = default;

    std::optional<std::string> checkSemantics() final;
    std::optional<IRReturnVal> generateIR() final;
};

}  // namespace ast

#endif
