#include "tac.h"
#include <utility>
using std::string;

TAC::TAC() {
    this->op = "uninitialized";
    this->lhs = "uninitialized";
    this->rhs = "uninitialized";
    this->result = "uninitialized";
}

TAC::TAC(string op, string lhs, string rhs, string result)
    : op(std::move(op)), lhs(std::move(lhs)), rhs(std::move(rhs)), result(std::move(result)) {}

void TAC::setOP(std::string _op) {
    this->op = std::move(_op);
}

void TAC::setLHS(std::string _lhs) {
    this->lhs = std::move(_lhs);
}

void TAC::setRHS(std::string _rhs) {
    this->rhs = std::move(_rhs);
}

void TAC::setResult(std::string _result) {
    this->result = std::move(_result);
}

std::string TAC::getOP() const {
    return this->op;
}

std::string TAC::getLHS() const {
    return this->lhs;
}

std::string TAC::getRHS() const {
    return this->rhs;
}

std::string TAC::getResult() const {
    return this->result;
}

std::string TAC::printInfo() const {
    return this->result + " := " + this->lhs + " " + this->op + " " + this->rhs;
}
