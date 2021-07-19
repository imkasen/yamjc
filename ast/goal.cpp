#include "goal.h"
using std::string;

Goal::Goal() : Node() {}

Goal::Goal(string t, string v) : Node(t, v) {}

std::optional<string> Goal::execute()
{
    for (const auto child : children)
    {
        string class_type, class_name;
        std::shared_ptr<STClass> st_class = nullptr;

        Node::st->setScopeTitle("Program");

        if (child.getType() == "MainClass")
        {
            class_type = "int";

            Node::st->enterScope(); // enter class scope
            class_name = child.execute();
            Node::st->setScopeTitle("Class:" + class_name);
            Node::st->exitScope(); // exit class scope

            st_class = std::make_shared<STClass>(class_name, class_type);
            Node::st->addRecord(class_name, st_class);
        }
        else // child.getType() == "ClassDeclaration"
        {
            Node::st->enterScope(); // enter class scope
            class_type = class_name = child.execute();
            Node::st->setScopeTitle("Class:" + class_name);
            Node::st->exitScope(); // exit class scope

            st_class = std::make_shared<STClass>(class_name, class_type);
            Node::st->addRecord(class_name, st_class);
        }
    }

    return std::nullopt;
}