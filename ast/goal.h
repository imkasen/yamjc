#ifndef GOAL_H
#define GOAL_H

#include "node.h"

class Goal : public Node
{
public:
    Goal();
    Goal(string t, string v);
};

#endif