#ifndef NODE_H
#define NODE_H

#include "../st/symbol_table.h"
#include <iostream>
#include <string>
#include <deque>
#include <fstream>

/*
 * The basic class in abstract syntax tree.
 *
 * Goal : Node
 * MainClass : Node
 * ...
 * Identifier : Node
 */
class Node
{
protected:
    size_t id;
    std::string type, value;
    static std::shared_ptr<SymbolTable> st;

public:
    /*
     * an awkward design,
     * Bison does not support smart pointers well,
     * so raw pointer is used.
     */
    std::deque<Node *> children;

    Node();
    Node(std::string t, std::string v);

    void setId(size_t n_id);
    void setType(std::string n_type);
    void setValue(std::string n_value);
    const size_t getId() const;
    const std::string getType() const;
    const std::string getValue() const;

    // AST
    // void printAST(size_t depth = 0);
    void saveAST(std::ofstream *outStream, size_t depth = 0);
    void generateAST(size_t &count, std::ofstream *outStream);

    // ST
    void buildST(std::shared_ptr<SymbolTable> &symbol_table);
    virtual std::string execute(Node *node) = 0;

    virtual ~Node();
};

#endif