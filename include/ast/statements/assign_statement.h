#ifndef AST_STATEMENTS_ASSIGN_STATEMENT_H
#define AST_STATEMENTS_ASSIGN_STATEMENT_H

#include "cfg/ir_copy.h"
#include "statement.h"

namespace ast {

class AssignStatement : public Statement {
public:
    AssignStatement();
    AssignStatement(std::string t, std::string v);
    ~AssignStatement() override = default;

    std::optional<std::string> checkSemantics() final;
    std::optional<IRReturnVal> generateIR() final;
};

}  // namespace ast

#endif
