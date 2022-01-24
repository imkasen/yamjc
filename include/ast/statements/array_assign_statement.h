#ifndef ARRAY_ASSIGN_STATEMENT_H
#define ARRAY_ASSIGN_STATEMENT_H

#include "ast/node.h"

class ArrayAssignStatement : public Node {
public:
    ArrayAssignStatement();
    ArrayAssignStatement(std::string t, std::string v);
};

#endif
