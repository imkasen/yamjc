#ifndef AST_PRIMARY_EXPRESSIONS_ARRAY_ALLOC_EXPRESSION_H
#define AST_PRIMARY_EXPRESSIONS_ARRAY_ALLOC_EXPRESSION_H

#include "cfg/ir_array_alloc.h"
#include "primary_expression.h"

namespace ast {

class ArrayAllocExpression : public PrimaryExpression {
public:
    ArrayAllocExpression() = delete;
    [[maybe_unused]] ArrayAllocExpression(std::string t, std::string v);
    ~ArrayAllocExpression() override = default;

    std::optional<std::string> checkSemantics() final;
    IRReturnVal generateIR() final;
};

}  // namespace ast

#endif
