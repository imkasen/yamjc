#include "ir_array_length.h"
using cfg::IRArrayLength;
using std::string;

IRArrayLength::IRArrayLength(string lhs, string result)
    : Tac("length", std::move(lhs), "", std::move(result)) {}

string IRArrayLength::printInfo() const {
    return this->getResult() + " := " + this->getOP() + " " + this->getLHS();
}

/*
 * TAC:
 *   x := length y
 * ByteCode:
 *   arraylength y
 *   istore x
 */
string IRArrayLength::printBC() const {
    string context;
    context += "arraylength " + this->getLHS() + "\n";
    context += "istore " + this->getResult() + "\n";
    return context;
}
