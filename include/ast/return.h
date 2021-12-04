#ifndef RETURN_H
#define RETURN_H

#include "node.h"

class Return : public Node {
public:
    Return();
    Return(std::string t, std::string v);

    std::optional<std::string> checkSemantics() override;
};

#endif
