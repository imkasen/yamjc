#include "ir_unary_expression.h"
using cfg::IRUnaryExpression;
using std::string;

IRUnaryExpression::IRUnaryExpression() : Tac() {}
IRUnaryExpression::IRUnaryExpression(string op, string lhs, string result)
    : Tac(std::move(op), std::move(lhs), "", std::move(result)) {}

std::string IRUnaryExpression::printInfo() const {
    return this->getResult() + " := " + this->getOP() + " " + this->getLHS();
}

/*
 * TAC:
 *   x := op y
 * ByteCode:
 *   "!":
 *     iconst || iload y
 *     iconst 1
 *     ixor
 *   "-":
 *     iconst || iload y
 *     ineg
 *   istrore x
 */
string IRUnaryExpression::printBC() const {
    string context;
    context += Tac::isNum(this->getLHS()) ? ("iconst " + this->getLHS()) : ("iload " + getLHS());
    context += "\n";
    if (this->getOP() == "!") {
        context += "iconst 1\n";
        context += "ixor\n";
    } else if (this->getOP() == "-") {
        context += "ineg\n";
    }
    context += "istore " + this->getResult() + "\n";
    return context;
}
