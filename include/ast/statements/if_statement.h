#ifndef IF_STATEMENT_H
#define IF_STATEMENT_H

#include "statement.h"

class IfStatement : public Statement {
public:
    IfStatement();
    IfStatement(std::string t, std::string v);
    ~IfStatement() override = default;

    std::optional<std::string> checkSemantics() final;
};

#endif
