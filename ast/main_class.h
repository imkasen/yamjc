#ifndef MAIN_CLASS_H
#define MAIN_CLASS_H

#include "node.h"

class MainClass : public Node
{
public:
    MainClass();
    MainClass(std::string t, std::string v);

    virtual std::optional<std::string> generateST() override;
};

#endif