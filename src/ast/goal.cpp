#include "ast/goal.h"
using std::string;

/*
                       "Goal"
              /          |                      \
     "MainClass"   ["ClassDeclaration"]  ["ClassExtendsDeclaration"]
 */

Goal::Goal() : Node() {}
Goal::Goal(string t, string v) : Node(std::move(t), std::move(v)) {}

/*
 * Note: Records in the current "Program" scope are added
 * by children scopes.
 *
 * @brief:
 *   1. Set the current scope title.
 *   2. Traverse children nodes.
 * @return: std::nullopt
 */
std::optional<string> Goal::generateST() {
    // 1.
    Goal::st.setScopeTitle("Program");

    // 2.
    for (const auto &child : this->children) {
        Goal::st.enterScope();  // Enter each "Class" scope
        child->generateST();
        Goal::st.exitScope();   // Exit "Class" scope
    }

    return std::nullopt;
}

/*
 * @brief: Traverse children nodes.
 * @return: std::nullopt
 */
std::optional<string> Goal::checkSemantics() {
    for (const auto &child : this->children) {
        Goal::st.enterScope();  // Enter "Class" scope
        child->checkSemantics();
        Goal::st.exitScope();   // Exit "Class" scope
    }
    return std::nullopt;
}
