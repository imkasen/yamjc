#include "ir_alloc.h"
using cfg::IRAlloc;
using std::string;

IRAlloc::IRAlloc(string lhs, string result) : Tac("new", std::move(lhs), "", std::move(result)) {}

string IRAlloc::printInfo() const {
    return this->getResult() + " := " + this->getOP() + " " + this->getLHS();
}

/*
 * TAC:
 *   x := new TYPE
 * ByteCode:
 *   new TYPE
 *   astore x
 */
string IRAlloc::printBC() const {
    string context;
    context += "new " + this->getLHS() + "\n";
    context += "astore " + this->getResult() + "\n";
    return context;
}
