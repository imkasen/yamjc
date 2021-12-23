#include "ast/node.h"
using std::cout;
using std::endl;
using std::size_t;
using std::string;

Node::Node() {
    // Bison needs this
    this->type = "uninitialised";
    this->value = "uninitialised";
}

Node::Node(string t, string v) : type(std::move(t)), value(std::move(v)) {}

Node::~Node() {
    for (auto child : this->children) {
        delete child;
    }
    this->children.clear();
}

void Node::setId(size_t n_id) {
    this->id = n_id;
}

void Node::setType(string n_type) {
    this->type = std::move(n_type);
}

void Node::setValue(string n_value) {
    this->value = std::move(n_value);
}

size_t Node::getId() const {
    return this->id;
}

string Node::getType() const {
    return this->type;
}

string Node::getValue() const {
    return this->value;
}

// Print ast in the command line.
/*
void Node::printAST(size_t depth) {
    for (size_t i = 0; i < depth; ++i) {
        cout << "  ";
    }
    cout << this->getType() << ":" << this->getValue() << endl;
    for (auto i = this->children.begin(); i != this->children.end(); ++i) {
        (*i)->printAST(depth + 1);
    }
}
*/

// Save ast in "ast.txt"
void Node::saveAST(std::ofstream *outStream, size_t depth) {  // NOLINT
    for (size_t i = 0; i < depth; ++i) {
        *outStream << "  ";
    }
    *outStream << this->getType() << ":" << this->getValue() << endl;
    for (auto child : this->children) {
        child->saveAST(outStream, depth + 1);
    }
}

// Generate ast in "ast.dot"
void Node::generateAST(std::ofstream *outStream, size_t &count) {  // NOLINT
    this->setId(count++);
    if (!this->getValue().empty()) {
        *outStream << "n" << this->getId() << " [label=\"" << this->getType() << ":" << this->getValue() << "\"];"
                   << endl;
    } else {
        *outStream << "n" << this->getId() << " [label=\"" << this->getType() << "\"];" << endl;
    }
    for (auto child : this->children) {
        child->generateAST(outStream, count);
        *outStream << "n" << this->getId() << " -> n" << child->getId() << ";" << endl;
    }
}

// Generate the symbol table
void Node::buildST(std::ofstream *outStream) {
    this->generateST();
    Node::st.resetTable();
    // Generate "st.dot"
    Node::st.printST(outStream);
}

std::optional<string> Node::generateST() {  // NOLINT
    for (auto child : this->children) {
        child->generateST();
    }
    return std::nullopt;
}

void Node::semanticAnalysis() {
    this->checkSemantics();
    Node::st.resetTable();
}

std::optional<string> Node::checkSemantics() {  // NOLINT
    for (auto child : this->children) {
        child->checkSemantics();
    }
    return std::nullopt;
}
