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
    std::size_t id = 0;
    std::string type, value;

public:
    /*
     * An awkward design,
     * should use the smart pointer here,
     * but bison does not support the smart pointer well.
     */
    std::deque<Node *> children;
    inline static SymbolTable st = SymbolTable();

    Node();
    Node(std::string t, std::string v);

    void setId(std::size_t n_id);
    void setType(std::string n_type);
    void setValue(std::string n_value);
    [[nodiscard]] std::size_t getId() const;
    [[nodiscard]] std::string getType() const;
    [[nodiscard]] std::string getValue() const;

    // AST
    // void printAST(std::size_t depth = 0);
    void saveAST(std::ofstream *outStream, std::size_t depth = 0);
    void generateAST(std::size_t &count, std::ofstream *outStream);

    // ST
    void buildST(std::ofstream *outStream);
    virtual std::optional<std::string> generateST();

    virtual ~Node();
};

#endif