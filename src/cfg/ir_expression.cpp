#include "ir_expression.h"
using cfg::IRExpression;
using std::string;

IRExpression::IRExpression() : Tac() {}
IRExpression::IRExpression(string op, string lhs, string rhs, string result)
    : Tac(std::move(op), std::move(lhs), std::move(rhs), std::move(result)) {}

string IRExpression::printInfo() const {
    return this->getResult() + " := " + this->getLHS() + " " + this->getOP() + " " + this->getRHS();
}

/*
 * TAC:
 *   x := y op z
 * ByteCode:
 *   iload || iconst y
 *   iload || iconst z
 *
 *   iadd || isub || imul || idiv
 *   iand || ior
 *   if_icmpeq || if_icmpne || if_icmpge || if_icmpgt || if_icmple || if_icmplt
 *
 *   istore x
 */
string IRExpression::printBC() const {
    string op = this->getOP();
    string context;
    context += isNum(this->getLHS()) ? ("iconst " + this->getLHS()) : ("iload " + this->getLHS());
    context += "\n";
    context += isNum(this->getRHS()) ? ("iconst " + this->getRHS()) : ("iload " + this->getRHS());
    context += "\n";

    if (op == "+") {
        context += "iadd";
    } else if (op == "-") {
        context += "isub";
    } else if (op == "*") {
        context += "imul";
    } else if (op == "/") {
        context += "idiv";
    } else if (op == "&&") {
        context += "iand";
    } else if (op == "||") {
        context += "ior";
    } else if (op == "==") {
        context += "if_icmpeq";
    } else if (op == "!=") {
        context += "if_icmpne";
    } else if (op == ">=") {
        context += "if_icmpge";
    } else if (op == ">") {
        context += "if_icmpgt";
    } else if (op == "<=") {
        context += "if_icmple";
    } else if (op == "<") {
        context += "if_icmplt";
    }
    context += "\n";

    context += "istore " + this->getResult() + "\n";
    return context;
}
