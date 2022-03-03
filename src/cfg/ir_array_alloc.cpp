#include "ir_array_alloc.h"
using cfg::IRArrayAlloc;
using std::string;

IRArrayAlloc::IRArrayAlloc() : Tac() {}
IRArrayAlloc::IRArrayAlloc(string rhs, string result)
    : Tac("new", "int[]", std::move(rhs), std::move(result)) {}

string IRArrayAlloc::printInfo() const {
    return this->getResult() + " := " + this->getOP() + " " + this->getLHS() + ", " + this->getRHS();
}

/*
 * TAC:
 *   x := new int, N
 * ByteCode:
 *   iconst N
 *   newarray int
 *   astore x
 */
string IRArrayAlloc::printBC() const {
    string context;
    context += "iconst " + this->getRHS() + "\n";
    context += "newarray int\n";
    context += "astore " + this->getResult() + "\n";
    return context;
}
