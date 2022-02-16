#include "ir_copy.h"
using std::string;

IRCopy::IRCopy() : Tac() {}
IRCopy::IRCopy(string lhs, string result) : Tac("", std::move(lhs), "", std::move(result)) {}
