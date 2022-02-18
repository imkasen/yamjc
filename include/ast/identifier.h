#ifndef AST_IDENTIFIER_H
#define AST_IDENTIFIER_H

#include "node.h"

namespace ast {

class Identifier : public Node {
public:
    Identifier();
    Identifier(std::string t, std::string v);
    ~Identifier() override = default;

    std::optional<std::string> generateST() override;
    std::optional<std::string> checkSemantics() override;
};

}  // namespace ast

#endif
