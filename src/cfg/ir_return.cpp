#include "ir_return.h"
using cfg::IRReturn;
using std::string;

IRReturn::IRReturn() : Tac() {}
IRReturn::IRReturn(string lhs) : Tac("return", std::move(lhs), "", "") {}

std::string IRReturn::printInfo() const {
    return this->getOP() + " " + this->getLHS();
}
