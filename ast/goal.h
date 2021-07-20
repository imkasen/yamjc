#ifndef GOAL_H
#define GOAL_H

#include "node.h"

class Goal : public Node
{
public:
    Goal();
    Goal(std::string t, std::string v);

    // ST
    virtual std::optional<std::string> execute() override;
};

#endif