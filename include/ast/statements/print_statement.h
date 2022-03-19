#ifndef AST_STATEMENTS_PRINT_STATEMENT_H
#define AST_STATEMENTS_PRINT_STATEMENT_H

#include "cfg/ir_method_call.h"
#include "cfg/ir_argument.h"
#include "statement.h"

namespace ast {

class PrintStatement : public Statement {
public:
    PrintStatement() = delete;
    [[maybe_unused]] PrintStatement(std::string t, std::string v);
    ~PrintStatement() override = default;

    std::optional<std::string> checkSemantics() final;
    std::optional<IRReturnVal> generateIR() final;
};

}  // namespace ast

#endif
