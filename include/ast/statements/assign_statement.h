#ifndef AST_STATEMENTS_ASSIGN_STATEMENT_H
#define AST_STATEMENTS_ASSIGN_STATEMENT_H

#include "statement.h"

namespace ast {

class AssignStatement : public Statement {
public:
    AssignStatement();
    AssignStatement(std::string t, std::string v);
    ~AssignStatement() override = default;

    std::optional<std::string> checkSemantics() final;
};

}

#endif
