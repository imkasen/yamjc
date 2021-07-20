#ifndef METHOD_BODY_H
#define METHOD_BODY_H

#include "node.h"

class MethodBody : public Node
{
public:
    MethodBody();
    MethodBody(std::string t, std::string v);

    // ST
    virtual std::optional<std::string> execute() override;
};

#endif
