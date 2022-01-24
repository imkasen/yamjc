#ifndef PRINT_STATEMENT_H
#define PRINT_STATEMENT_H

#include "ast/node.h"

class PrintStatement : public Node {
public:
    PrintStatement();
    PrintStatement(std::string t, std::string v);
};

#endif
