#ifndef AST_MAIN_CLASS_H
#define AST_MAIN_CLASS_H

#include "node.h"

namespace ast {

class MainClass : public Node {
public:
    MainClass();
    MainClass(std::string t, std::string v);
    ~MainClass() override = default;

    std::optional<std::string> generateST() final;
    std::optional<std::string> checkSemantics() final;
    std::optional<IRReturnVal> generateIR() final;
};

}  // namespace ast

#endif