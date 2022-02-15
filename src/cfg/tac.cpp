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

void TAC::setOP(const std::string &_op) {
    this->op = _op;
}

void TAC::setLHS(const std::string &_lhs) {
    this->lhs = _lhs;
}

void TAC::setRHS(const std::string &_rhs) {
    this->rhs = _rhs;
}

void TAC::setResult(const std::string &_result) {
    this->result = _result;
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

std::string TAC::print() const {
    return this->result + " := " + this->lhs + " " + this->op + " " + this->rhs;
}
