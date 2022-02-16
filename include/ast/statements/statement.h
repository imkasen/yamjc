#ifndef AST_STATEMENTS_STATEMENT_H
#define AST_STATEMENTS_STATEMENT_H

#include "ast/node.h"

class Statement : public Node {
public:
    Statement();
    Statement(std::string t, std::string v);
    ~Statement() override = default;

    std::optional<std::string> generateST() final;
};

#endif