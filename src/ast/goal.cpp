#include "ast/goal.h"
using std::string;

Goal::Goal() : Node() {}
Goal::Goal(string t, string v) : Node(std::move(t), std::move(v)) {}

/*
 * Set the current scope title.
 * Traverse children.
 * Records in "Program" scope added by children scope(MainClass, ClassDeclaration).
 *
 * @return: std::nullopt
 */
std::optional<string> Goal::generateST() {
    Goal::st.setScopeTitle("Program");

    for (auto &child : this->children) {
        // enter class scope
        Goal::st.enterScope();
        child->generateST();
        Goal::st.exitScope();  // exit class scope
    }

    return std::nullopt;
}

std::optional<std::string> Goal::checkSemantics() {
    for (auto &child : this->children) {
        // enter class scope
        Goal::st.enterScope();
        child->checkSemantics();
        Goal::st.exitScope();  // exit class scope
    }

    return std::nullopt;
}
