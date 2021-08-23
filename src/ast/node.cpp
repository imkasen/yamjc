#include "ast/node.h"
using std::string;
using std::size_t;
using std::cout;
using std::endl;

Node::Node() // Bison needs this
{
    this->type = "uninitialised";
    this->value = "uninitialised";
}

Node::Node(string t, string v) : type(std::move(t)), value(std::move(v)) {}

Node::~Node()
{
    for (auto && child : this->children)
    {
        delete child;
    }
    this->children.clear();
}

void Node::setId(size_t n_id)
{
    this->id = n_id;
}

void Node::setType(std::string n_type)
{
    this->type = std::move(n_type);
}

void Node::setValue(std::string n_value)
{
    this->value = std::move(n_value);
}

size_t Node::getId() const
{
    return this->id;
}

std::string Node::getType() const
{
    return this->type;
}

std::string Node::getValue() const
{
    return this->value;
}

// Print ast in the command line.
/*
void Node::printAST(size_t depth)
{
    for (size_t i = 0; i < depth; ++i)
    {
        cout << "  ";
    }
    cout << this->getType() << ":" << this->getValue() << endl;
    for (auto i = this->children.begin(); i != this->children.end(); ++i)
    {
        (*i)->printAST(depth + 1);
    }
}
*/

// Save ast in the ast.txt.
void Node::saveAST(std::ofstream *outStream, size_t depth)
{
    for (size_t i = 0; i < depth; ++i)
    {
        *outStream << "  ";
    }
    *outStream << this->getType() << ":" << this->getValue() << endl;
    for (auto &child : this->children)
    {
        child->saveAST(outStream, depth + 1);
    }
}

// Generate ast in the ast.dot.
void Node::generateAST(size_t &count, std::ofstream *outStream)
{
    this->setId(count++);
    if (!this->getValue().empty())
    {
        *outStream << "n" << this->getId() << " [label=\"" << this->getType() << ":" << this->getValue() << "\"];" << endl;
    }
    else
    {
        *outStream << "n" << this->getId() << " [label=\"" << this->getType() << "\"];" << endl;
    }
    for (auto &child : this->children)
    {
        child->generateAST(count, outStream);
        *outStream << "n" << this->getId() << " -> n" << child->getId() << ";" << endl;
    }
}

// Generate symbol table
void Node::buildST(std::ofstream *outStream)
{
    this->generateST();
    Node::st.resetTable();
    // generate st.dot
    Node::st.printST(outStream);
}

std::optional<std::string> Node::generateST()
{
    for (auto &child: this->children)
    {
        child->generateST();
    }

    return std::nullopt;
}
