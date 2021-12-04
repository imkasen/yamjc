#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "node.h"

class Expression : public Node {
private:
    bool checkParameters(const std::shared_ptr<Record> &m_record_ptr);
    static void strSplit(std::deque<std::string> &deque, const std::string &text, const std::string &delimiter);

public:
    Expression();
    Expression(std::string t, std::string v);

    std::optional<std::string> checkSemantics() override;
};

#endif