#ifndef AST_EXPRESSIONS_ARRAY_LENGTH_EXPRESSION_H
#define AST_EXPRESSIONS_ARRAY_LENGTH_EXPRESSION_H

#include "cfg/ir_array_length.h"
#include "expression.h"

namespace ast {

class ArrayLengthExpression : public Expression {
public:
    ArrayLengthExpression() = delete;
    [[maybe_unused]] ArrayLengthExpression(std::string t, std::string v);
    ~ArrayLengthExpression() override = default;

    std::optional<std::string> checkSemantics() final;
    IRReturnVal generateIR() final;
};

}  // namespace ast

#endif
