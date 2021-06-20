#include "node.h"
using std::string;
using std::cout;
using std::endl;

Node::Node() // Bison needs this
{
    this->type = "uninitialised";
    this->value = "uninitialised";
}

Node::Node(string t, string v) : type(t), value(v) {}

// Print ast in the command line.
void Node::printAST(int depth)
{
    for (int i = 0; i < depth; ++i)
    {
        cout << "  ";
    }
    cout << this->type << ":" << this->value << endl;
    for (auto i = this->children.begin(); i != this->children.end(); ++i)
    {
        (*i)->printAST(depth + 1);
    }
}

// Save ast in the ast.txt.
void Node::saveAST(std::ofstream *outStream, int depth)
{
    for (int i = 0; i < depth; ++i)
    {
        *outStream << "  ";
    }
    *outStream << this->type << ":" << this->value << endl;
    for (auto i = this->children.begin(); i != this->children.end(); ++i)
    {
        (*i)->saveAST(outStream, depth + 1);
    }
}

// Generate ast in the ast.dot.
void Node::generateAST(int &count, std::ofstream *outStream)
{
    this->id = ++count;
    if (this->value != "")
    {
        *outStream << "n" << this->id << " [label=\"" << this->type << ":" << this->value << "\"];" << endl;
    }
    else
    {
        *outStream << "n" << this->id << " [label=\"" << this->type << "\"];" << endl;
    }
    for (auto i = this->children.begin(); i != this->children.end(); ++i)
    {
        (*i)->generateAST(count, outStream);
        *outStream << "n" << this->id << " -> n" << (*i)->id << endl;
    }
}
