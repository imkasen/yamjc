#ifndef AST_MAIN_CLASS_H
#define AST_MAIN_CLASS_H

#include "node.h"

class MainClass : public Node {
public:
    MainClass();
    MainClass(std::string t, std::string v);
    ~MainClass() override = default;

    std::optional<std::string> generateST() override;
    std::optional<std::string> checkSemantics() override;
};

#endif