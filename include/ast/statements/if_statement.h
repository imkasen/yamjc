#ifndef IF_STATEMENT_H
#define IF_STATEMENT_H

#include "ast/node.h"

class IfStatement : public Node {
public:
    IfStatement();
    IfStatement(std::string t, std::string v);
};

#endif
