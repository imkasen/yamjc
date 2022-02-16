#ifndef AST_EXPRESSIONS_EXPRESSION_LIST_H
#define AST_EXPRESSIONS_EXPRESSION_LIST_H

#include "ast/node.h"

class ExpressionList : public Node {
public:
    ExpressionList();
    ExpressionList(std::string t, std::string v);
    ~ExpressionList() override = default;

    std::optional<std::string> checkSemantics() final;
};

#endif
