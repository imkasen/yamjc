#ifndef STATEMENT_H
#define STATEMENT_H

#include "ast/node.h"

class Statement : public Node {
public:
    Statement();
    Statement(std::string t, std::string v);

    std::optional<std::string> checkSemantics() override;
};

#endif