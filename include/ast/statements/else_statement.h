#ifndef ELSE_STATEMENT_H
#define ELSE_STATEMENT_H

#include "ast/node.h"

class ElseStatement : public Node {
public:
    ElseStatement();
    ElseStatement(std::string t, std::string v);
    ~ElseStatement() override = default;
};

#endif
