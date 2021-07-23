#ifndef TYPE_H
#define TYPE_H

#include "node.h"

class Type : public Node
{
public:
    Type();
    Type(std::string t, std::string v);

    virtual std::optional<std::string> generateST() override;
};

#endif