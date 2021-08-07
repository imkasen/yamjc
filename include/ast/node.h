#ifndef NODE_H
#define NODE_H

#include "st/variable.h"
#include "st/parameter.h"
#include "st/method.h"
#include "st/st_class.h"
#include "st/symbol_table.h"
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
    std::size_t id;
    std::string type, value;

public:
    /*
     * An awkward design.
     * Should use the smart pointer here,
     * but the smart pointer is too complicated in bison.
     */
    std::deque<Node *> children;
    inline static SymbolTable st = SymbolTable();

    Node();
    Node(std::string t, std::string v);

    void setId(std::size_t n_id);
    void setType(std::string n_type);
    void setValue(std::string n_value);
    const std::size_t getId() const;
    const std::string getType() const;
    const std::string getValue() const;

    // AST
    // void printAST(std::size_t depth = 0);
    void saveAST(std::ofstream *outStream, std::size_t depth = 0);
    void generateAST(std::size_t &count, std::ofstream *outStream);

    // ST
    void buildST(std::ofstream *outStream);
    virtual std::optional<std::string> generateST();

    virtual ~Node() = default;
};

#endif