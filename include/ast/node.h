#ifndef AST_NODE_H
#define AST_NODE_H

#include <cstdlib>
#include <fstream>
#include "st/st_class.h"
#include "st/symbol_table.h"

namespace ast {

/*
 * The basic class in abstract syntax tree.
 *
 * Goal : Node
 * MainClass : Node
 * ...
 * Identifier : Node
 */
class Node {
protected:
    std::size_t id = 0;
    std::string type, value;

public:
    std::deque<std::shared_ptr<Node>> children;
    inline static st::SymbolTable st = st::SymbolTable();  // NOLINT

    Node();
    Node(std::string t, std::string v);
    virtual ~Node() = default;

    void setId(std::size_t _id);
    void setType(std::string _type);
    void setValue(std::string _value);
    [[nodiscard]] std::size_t getId() const;
    [[nodiscard]] std::string getType() const;
    [[nodiscard]] std::string getValue() const;

    // Functions related to the abstract syntax tree
    // void printAST(std::size_t depth = 0);
    void saveAST(std::ofstream* outStream, std::size_t depth = 0);
    void generateAST(std::ofstream* outStream, std::size_t &count);

    // Functions related to the symbol table
    void buildST(std::ofstream* outStream);
    virtual std::optional<std::string> generateST();

    // Functions related to the semantic Analysis
    void semanticAnalysis();
    virtual std::optional<std::string> checkSemantics();

    static void printErrMsg(const std::string &message);
};

}  // namespace ast

#endif