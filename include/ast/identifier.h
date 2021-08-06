#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "node.h"

class Identifier : public Node
{
public:
    Identifier();
    Identifier(std::string t, std::string v);

    std::optional<std::string> generateST() override;
};

#endif
