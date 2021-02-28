#include "node.h"

Node::Node() // Bison needs this
{
    type = "uninitialised";
    value = "uninitialised";
}

Node::Node(string t, string v) : type(t), value(v) {}

void Node::print_tree(int depth)
{
    for (int i = 0; i < depth; ++i)
        cout << "  ";
    cout << type << ":" << value << endl;
    for (auto i = children.begin(); i != children.end(); ++i)
        (*i)->print_tree(depth + 1);
}

void Node::generate_tree(int &count, std::ofstream *outStream)
{
    id = ++count;
    *outStream << "n" << id << " [label=\"" << type << ":" << value << "\"];" << endl;

    for (auto i = children.begin(); i != children.end(); ++i)
    {
        (*i)->generate_tree(count, outStream);
        *outStream << "n" << id << " -> n" << (*i)->id << endl;
    }
}
