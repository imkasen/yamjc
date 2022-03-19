#ifndef AST_STATEMENTS_ASSIGN_STATEMENT_H
#define AST_STATEMENTS_ASSIGN_STATEMENT_H

#include "cfg/ir_assign.h"
#include "statement.h"

namespace ast {

class AssignStatement : public Statement {
public:
    AssignStatement() = delete;
    [[maybe_unused]] AssignStatement(std::string t, std::string v);
    ~AssignStatement() override = default;

    std::optional<std::string> checkSemantics() final;
    std::optional<IRReturnVal> generateIR() final;
};

}  // namespace ast

#endif
