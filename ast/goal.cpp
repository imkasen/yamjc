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
    Node::st->setScopeTitle("Program");

    for (auto child : children)
    {
        Node::st->enterScope(); // enter class scope
        child->generateST();
        Node::st->exitScope(); // exit class scope
    }

    return std::nullopt;
}