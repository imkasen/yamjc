#ifndef AST_METHOD_BODY_H
#define AST_METHOD_BODY_H

#include "node.h"

namespace ast {

class MethodBody : public Node {
public:
    MethodBody();
    MethodBody(std::string t, std::string v);
    ~MethodBody() override = default;

    std::optional<std::string> generateST() override;
};

}  // namespace ast

#endif
