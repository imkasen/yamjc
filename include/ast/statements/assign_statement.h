#ifndef ASSIGN_STATEMENT_H
#define ASSIGN_STATEMENT_H

#include "ast/node.h"

class AssignStatement : public Node {
public:
    AssignStatement();
    AssignStatement(std::string t, std::string v);
};

#endif
