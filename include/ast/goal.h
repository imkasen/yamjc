#ifndef AST_GOAL_H
#define AST_GOAL_H

#include "node.h"

namespace ast {

class Goal : public Node {
public:
    Goal() = delete;
    Goal(std::string t, std::string v);
    ~Goal() override = default;

    std::optional<std::string> generateST() final;
    std::optional<std::string> checkSemantics() final;
    std::optional<IRReturnVal> generateIR() final;
};

}  // namespace ast

#endif