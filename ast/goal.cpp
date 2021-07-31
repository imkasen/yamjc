#include "goal.h"
using std::string;

Goal::Goal() : Node() {}
Goal::Goal(string t, string v) : Node(t, v) {}

/*
 * Set the current scope title.
 * Traverse children.
 * Records in "Program" scope added by children scope(MainClass, ClassDeclaration).
 *
 * @return: std::nullopt
 */
std::optional<string> Goal::generateST()
{
    Goal::st.setScopeTitle("Program");

    for (auto child : children)
    {
        Goal::st.enterScope(); // enter class scope
        child->generateST();
        Goal::st.exitScope(); // exit class scope
    }

    return std::nullopt;
}