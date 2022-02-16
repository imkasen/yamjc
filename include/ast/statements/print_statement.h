#ifndef AST_STATEMENTS_PRINT_STATEMENT_H
#define AST_STATEMENTS_PRINT_STATEMENT_H

#include "statement.h"

class PrintStatement : public Statement {
public:
    PrintStatement();
    PrintStatement(std::string t, std::string v);
    ~PrintStatement() override = default;

    std::optional<std::string> checkSemantics() final;
};

#endif
