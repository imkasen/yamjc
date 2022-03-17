#ifndef AST_STATEMENTS_WHILE_STATEMENT_H
#define AST_STATEMENTS_WHILE_STATEMENT_H

#include "cfg/ir_cond_jump.h"
#include "cfg/ir_jump.h"
#include "statement.h"

namespace ast {

class WhileStatement : public Statement {
public:
    WhileStatement() = delete;
    WhileStatement(std::string t, std::string v);
    ~WhileStatement() override = default;

    std::optional<std::string> checkSemantics() final;
    std::optional<IRReturnVal> generateIR() final;
};

}  // namespace ast

#endif
