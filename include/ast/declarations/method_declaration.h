#ifndef METHOD_DECLARATION_H
#define METHOD_DECLARATION_H

#include "ast/node.h"

class MethodDeclaration : public Node {
public:
    MethodDeclaration();
    MethodDeclaration(std::string t, std::string v);

    std::optional<std::string> generateST() override;
    std::optional<std::string> checkSemantics() override;
};

#endif