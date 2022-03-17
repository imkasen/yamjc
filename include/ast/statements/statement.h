#ifndef AST_STATEMENTS_STATEMENT_H
#define AST_STATEMENTS_STATEMENT_H

#include "ast/node.h"

namespace ast {

class Statement : public Node {
public:
    Statement() = delete;
    Statement(std::string t, std::string v);
    ~Statement() override = default;

    std::optional<std::string> generateST() final;
    std::optional<IRReturnVal> generateIR() override;
};

}  // namespace ast

#endif