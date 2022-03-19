#ifndef AST_STATEMENTS_ARRAY_ASSIGN_STATEMENT_H
#define AST_STATEMENTS_ARRAY_ASSIGN_STATEMENT_H

#include "statement.h"
#include "cfg/ir_array_assign.h"

namespace ast {

class ArrayAssignStatement : public Statement {
public:
    ArrayAssignStatement() = delete;
    [[maybe_unused]] ArrayAssignStatement(std::string t, std::string v);
    ~ArrayAssignStatement() override = default;

    std::optional<std::string> checkSemantics() final;
    std::optional<IRReturnVal> generateIR() final;
};

}

#endif
