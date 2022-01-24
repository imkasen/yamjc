#ifndef WHILE_STATEMENT_H
#define WHILE_STATEMENT_H

#include "ast/node.h"

class WhileStatement : public Node {
public:
    WhileStatement();
    WhileStatement(std::string t, std::string v);
};

#endif
