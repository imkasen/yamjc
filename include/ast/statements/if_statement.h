#ifndef AST_STATEMENTS_IF_STATEMENT_H
#define AST_STATEMENTS_IF_STATEMENT_H

#include "cfg/ir_cond_jump.h"
#include "cfg/ir_jump.h"
#include "statement.h"

namespace ast {

class IfStatement : public Statement {
public:
    IfStatement() = delete;
    [[maybe_unused]] IfStatement(std::string t, std::string v);
    ~IfStatement() override = default;

    std::optional<std::string> checkSemantics() final;
    IRReturnVal generateIR() final;
};

}  // namespace ast

#endif
