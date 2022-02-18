#ifndef AST_STATEMENTS_WHILE_STATEMENT_H
#define AST_STATEMENTS_WHILE_STATEMENT_H

#include "statement.h"

namespace ast {

class WhileStatement : public Statement {
public:
    WhileStatement();
    WhileStatement(std::string t, std::string v);
    ~WhileStatement() override = default;

    std::optional<std::string> checkSemantics() final;
};

}  // namespace ast

#endif
