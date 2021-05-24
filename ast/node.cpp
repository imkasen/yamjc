#include "node.h"

Node::Node() // Bison needs this
{
    type = "uninitialised";
    value = "uninitialised";
}

Node::Node(string t, string v) : type(t), value(v) {}

void Node::printTree(int depth)
{
    for (int i = 0; i < depth; ++i)
        cout << "  ";
    cout << this->type << ":" << this->value << endl;
    for (auto i = children.begin(); i != children.end(); ++i)
        (*i)->printTree(depth + 1);
}

void Node::saveTree(std::ofstream *outStream, int depth)
{
    for (int i = 0; i < depth; ++i)
        *outStream << "  ";
    *outStream << this->type << ":" << this->value << endl;
    for (auto i = children.begin(); i != children.end(); ++i)
        (*i)->saveTree(outStream, depth + 1);
}

void Node::generateTree(int &count, std::ofstream *outStream)
{
    this->id = ++count;
    if (value != "")
        *outStream << "n" << this->id << " [label=\"" << this->type << ":" << this->value << "\"];" << endl;
    else
        *outStream << "n" << this->id << " [label=\"" << this->type << "\"];" << endl;

    for (auto i = children.begin(); i != children.end(); ++i)
    {
        (*i)->generateTree(count, outStream);
        *outStream << "n" << this->id << " -> n" << (*i)->id << endl;
    }
}
