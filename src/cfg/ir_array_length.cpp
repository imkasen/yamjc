#include "ir_array_length.h"
using cfg::IRArrayLength;
using std::string;

IRArrayLength::IRArrayLength() : Tac() {}
IRArrayLength::IRArrayLength(string lhs, string result)
    : Tac("length", std::move(lhs), "", std::move(result)) {}
