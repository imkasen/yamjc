#ifndef ELSE_STATEMENT_H
#define ELSE_STATEMENT_H

#include "statement.h"

class ElseStatement : public Statement {
public:
    ElseStatement();
    ElseStatement(std::string t, std::string v);
};

#endif
