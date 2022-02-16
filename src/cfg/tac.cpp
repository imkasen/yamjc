#include "tac.h"
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

std::string Tac::getOP() const {
    return this->op;
}

std::string Tac::getLHS() const {
    return this->lhs;
}

std::string Tac::getRHS() const {
    return this->rhs;
}

std::string Tac::getResult() const {
    return this->result;
}

std::string Tac::printInfo() const {
    return this->result + " := " + this->lhs + " " + this->op + " " + this->rhs;
}
