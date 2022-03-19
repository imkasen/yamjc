#include "tac.h"
using cfg::Tac;
using std::string;

Tac::Tac(string op, string lhs, string rhs, string result)
    : op(std::move(op)), lhs(std::move(lhs)), rhs(std::move(rhs)), result(std::move(result)) {}

[[maybe_unused]] void Tac::setOP(std::string _op) {
    this->op = std::move(_op);
}

[[maybe_unused]] void Tac::setLHS(std::string _lhs) {
    this->lhs = std::move(_lhs);
}

[[maybe_unused]] void Tac::setRHS(std::string _rhs) {
    this->rhs = std::move(_rhs);
}

[[maybe_unused]] void Tac::setResult(std::string _result) {
    this->result = std::move(_result);
}

// prepare for a new entry "BasicBlock"
void Tac::resetID() {
    Tac::iid = 0;
    Tac::bid = 0;
    Tac::aid = 0;
    Tac::rid = 0;
    Tac::vid = 0;
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

string Tac::generateTmpVarName(const char &type) {
    switch (type) {
        case 'i': // int
            return "_i" + std::to_string(iid++);
        case 'b': // boolean
            return "_b" + std::to_string(bid++);
        case 'a': // array
            return "_a" + std::to_string(aid++);
        case 'r': // self-defined class
            return "_r" + std::to_string(rid++);
        case 'v': // void
        default:
            return "_v" + std::to_string(vid++);
    }
}

bool Tac::isNum(const string &str) {
     return std::all_of(str.cbegin(), str.cend(), [](unsigned char c){return std::isdigit(c);});
}
