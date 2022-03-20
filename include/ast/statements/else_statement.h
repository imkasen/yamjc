#ifndef AST_STATEMENTS_ELSE_STATEMENT_H
#define AST_STATEMENTS_ELSE_STATEMENT_H

#include "statement.h"

namespace ast {

class ElseStatement : public Statement {
public:
    ElseStatement() = delete;
    [[maybe_unused]] ElseStatement(std::string t, std::string v);
    ~ElseStatement() override = default;

    IRReturnVal generateIR() final;
};

}  // namespace ast

#endif
