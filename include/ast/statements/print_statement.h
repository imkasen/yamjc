#ifndef AST_STATEMENTS_PRINT_STATEMENT_H
#define AST_STATEMENTS_PRINT_STATEMENT_H

#include "statement.h"

namespace ast {

class PrintStatement : public Statement {
public:
    PrintStatement();
    PrintStatement(std::string t, std::string v);
    ~PrintStatement() override = default;

    std::optional<std::string> checkSemantics() final;
};

}  // namespace ast

#endif
