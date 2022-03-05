#ifndef AST_EXPRESSIONS_EXPRESSION_H
#define AST_EXPRESSIONS_EXPRESSION_H

#include "ast/node.h"
#include "cfg/ir_method_call.h"

namespace ast {

class Expression : public Node {
private:
    void checkParameters(const std::shared_ptr<st::Record> &m_record_ptr);
    static void strSplit(std::deque<std::string> &deque, std::string &text, const std::string &delimiter);

public:
    Expression();
    Expression(std::string t, std::string v);
    ~Expression() override = default;

    std::optional<std::string> generateST() final;
    std::optional<std::string> checkSemantics() override;
    std::optional<IRReturnVal> generateIR() override;
};

}  // namespace ast

#endif