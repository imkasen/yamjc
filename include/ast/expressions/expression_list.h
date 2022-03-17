#ifndef AST_EXPRESSIONS_EXPRESSION_LIST_H
#define AST_EXPRESSIONS_EXPRESSION_LIST_H

#include "ast/node.h"
#include "cfg/ir_argument.h"

namespace ast {

class ExpressionList : public Node {
public:
    ExpressionList() = delete;
    ExpressionList(std::string t, std::string v);
    ~ExpressionList() override = default;

    std::optional<std::string> checkSemantics() final;
    std::optional<IRReturnVal> generateIR() final;
};

}  // namespace ast

#endif
