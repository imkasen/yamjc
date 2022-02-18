#ifndef AST_STATEMENTS_IF_STATEMENT_H
#define AST_STATEMENTS_IF_STATEMENT_H

#include "statement.h"

namespace ast {

class IfStatement : public Statement {
public:
    IfStatement();
    IfStatement(std::string t, std::string v);
    ~IfStatement() override = default;

    std::optional<std::string> checkSemantics() final;
};

}  // namespace ast

#endif
