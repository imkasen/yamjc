#include "ir_method_call.h"
using cfg::IRMethodCall;
using std::string;

IRMethodCall::IRMethodCall() : Tac() {}
IRMethodCall::IRMethodCall(string lhs, string result)
    : Tac("call", std::move(lhs), "", std::move(result)) {}
