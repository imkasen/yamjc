#include "tac.h"
using cfg::Tac;
using std::string;

Tac::Tac() {
    this->op = "uninitialized";
    this->lhs = "uninitialized";
    this->rhs = "uninitialized";
    this->result = "uninitialized";
}

Tac::Tac(string op, string lhs, string rhs, string result)
    : op(std::move(op)), lhs(std::move(lhs)), rhs(std::move(rhs)), result(std::move(result)) {}

void Tac::setOP(std::string _op) {
    this->op = std::move(_op);
}

void Tac::setLHS(std::string _lhs) {
    this->lhs = std::move(_lhs);
}

void Tac::setRHS(std::string _rhs) {
    this->rhs = std::move(_rhs);
}

void Tac::setResult(std::string _result) {
    this->result = std::move(_result);
}

void Tac::resetID() {
    Tac::tmp_id = 0;
}

string Tac::getOP() const {
    return this->op;
}

string Tac::getLHS() const {
    return this->lhs;
}

string Tac::getRHS() const {
    return this->rhs;
}

string Tac::getResult() const {
    return this->result;
}

string Tac::generateTmpVarName() {
    return "_t" + std::to_string(Tac::tmp_id++);
}

string Tac::printInfo() const {
    return this->result + " := " + this->lhs + " " + this->op + " " + this->rhs;
}