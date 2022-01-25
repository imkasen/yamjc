#ifndef ASSIGN_STATEMENT_H
#define ASSIGN_STATEMENT_H

#include "statement.h"

class AssignStatement : public Statement {
public:
    AssignStatement();
    AssignStatement(std::string t, std::string v);
    ~AssignStatement() override = default;
};

#endif
