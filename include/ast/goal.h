#ifndef AST_GOAL_H
#define AST_GOAL_H

#include "node.h"

namespace ast {

class Goal : public Node {
public:
    Goal() = delete;
    [[maybe_unused]] Goal(std::string t, std::string v);
    ~Goal() override = default;

    std::optional<std::string> generateST() final;
    std::optional<std::string> checkSemantics() final;
    IRReturnVal generateIR() final;
};

}  // namespace ast

#endif