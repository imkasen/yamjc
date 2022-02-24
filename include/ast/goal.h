#ifndef AST_GOAL_H
#define AST_GOAL_H

#include "node.h"

namespace ast {

class Goal : public Node {
public:
    Goal();
    Goal(std::string t, std::string v);
    ~Goal() override = default;

    std::optional<std::string> generateST() override;
    std::optional<std::string> checkSemantics() override;
    std::optional<IRReturnVal> generateIR() override;
};

}  // namespace ast

#endif