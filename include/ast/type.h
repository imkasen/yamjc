#ifndef AST_TYPE_H
#define AST_TYPE_H

#include "node.h"

class Type : public Node {
public:
    Type();
    Type(std::string t, std::string v);
    ~Type() override = default;

    std::optional<std::string> generateST() override;
    std::optional<std::string> checkSemantics() override;
};

#endif