#ifndef AST_EXPRESSIONS_EXPRESSION_LIST_H
#define AST_EXPRESSIONS_EXPRESSION_LIST_H

#include "expression.h"
#include "cfg/ir_argument.h"

namespace ast {

class ExpressionList : public Expression {
public:
    ExpressionList() = delete;
    [[maybe_unused]] ExpressionList(std::string t, std::string v);
    ~ExpressionList() override = default;

    std::optional<std::string> checkSemantics() final;
    IRReturnVal generateIR() final;
};

}  // namespace ast

#endif
