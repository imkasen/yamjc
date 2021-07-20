#include "goal.h"
using std::string;

Goal::Goal() : Node() {}

Goal::Goal(string t, string v) : Node(t, v) {}

/*
 * Traverse children.
 * Records in "Program" scope added by children scope(MainClass, ClassDeclaration).
 *
 * @return: std::nullopt
 */
std::optional<string> Goal::execute()
{
    for (const auto child : children)
    {
        string class_name = "";
        Node::st->setScopeTitle("Program");

        Node::st->enterScope(); // enter class scope
        class_name = child.execute();
        Node::st->setScopeTitle("Class:" + class_name);
        Node::st->exitScope(); // exit class scope

        /*
        if (child.getType() == "MainClass")
        {
            Node::st->enterScope(); // enter class scope
            class_name = child.execute();
            Node::st->setScopeTitle("Class:" + class_name);
            Node::st->exitScope(); // exit class scope
        }
        else // child.getType() == "ClassDeclaration"
        {
            Node::st->enterScope(); // enter class scope
            class_name = child.execute();
            Node::st->setScopeTitle("Class:" + class_name);
            Node::st->exitScope(); // exit class scope

            //st_class = std::make_shared<STClass>(class_name, class_type);
            //Node::st->addRecord(class_name, st_class);
        }
         */
    }

    return std::nullopt;
}