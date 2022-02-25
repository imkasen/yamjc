#include "ir_copy.h"
using cfg::IRCopy;
using std::string;

IRCopy::IRCopy() : Tac() {}
IRCopy::IRCopy(string lhs, string result) : Tac("", std::move(lhs), "", std::move(result)) {}

std::string IRCopy::printInfo() const {
    return this->result + " := " + this->lhs;
}
