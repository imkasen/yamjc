#include "ir_method_call.h"
using cfg::IRMethodCall;
using std::string;

IRMethodCall::IRMethodCall() : Tac() {}
IRMethodCall::IRMethodCall(string lhs, string rhs, string result)
    : Tac("call", std::move(lhs), std::move(rhs), std::move(result)) {}

string IRMethodCall::printInfo() const {
    return this->getResult() + " := " + this->getOP() + " " + this->getLHS() + ", " + this->getRHS();
}

/*
 * TAC:
 *   x := call f, N
 * ByteCode:
 *   // "N" seems to be useless
 *   invokevirtual f
 *   istore x
 */
string IRMethodCall::printBC() const {
    string context;
    if (this->getLHS() == "__PRINT__") {
        context += "invokevirtual " + this->getLHS() + "\n";
    } else {
        context += "invokevirtual " + this->getLHS() + "\n";
        context += "istore " + this->getResult() + "\n";
    }
    return context;
}
