#ifndef AST_NODE_H
#define AST_NODE_H

#include <cstdlib>
#include <fstream>
#include <variant>
#include "cfg/basic_block.h"
#include "cfg/tac.h"
#include "st/st_class.h"
#include "st/symbol_table.h"

/*
 * Used as return value of "generateIR()".
 * 1. "std::monostate" is used as null.
 * 2. return "string" in "Expression".
 * 3. return "BasicBlock ptr" in "Statement".
 */
using IRReturnVal = std::variant<std::monostate, std::string, std::shared_ptr<cfg::BasicBlock>>;

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
private:
    std::size_t id = 0;
    std::string type, value;

public:
    std::deque<std::shared_ptr<Node>> children;
    inline static st::SymbolTable st = st::SymbolTable();                    // NOLINT
    inline static std::list<std::shared_ptr<cfg::BasicBlock>> bb_list = {};  // store all "BasicBlock"
    // link class, method with "BasicBlock",
    // "<class_name, <method_name, entry_block_name>>"
    inline static std::unordered_map<std::string, std::unordered_map<std::string, std::string>> blk_links = {};

    Node() = delete;
    Node(std::string t, std::string v);
    virtual ~Node() = default;

    void setId(std::size_t _id);
    [[maybe_unused]] void setType([[maybe_unused]] std::string _type);
    [[maybe_unused]] void setValue(std::string _value);
    [[nodiscard]] std::size_t getId() const;
    [[nodiscard]] std::string getType() const;
    [[nodiscard]] std::string getValue() const;

    // Functions related to the abstract syntax tree
    // void printAST(std::size_t depth = 0);
    // void saveAST(std::ofstream &ostream, std::size_t depth = 0);
    void generateAST(std::ofstream &ostream, std::size_t &count);

    // Functions related to the symbol table
    void buildST(std::ofstream &ostream);
    virtual std::optional<std::string> generateST();

    // Functions related to the semantic analysis
    void semanticAnalysis();
    virtual std::optional<std::string> checkSemantics();

    // Functions related to the control flow graph
    void buildCFG(std::ofstream &ostream);
    virtual std::optional<IRReturnVal> generateIR();
    static std::shared_ptr<cfg::BasicBlock> createBB();

    // Functions related to the bytecode generation
    static void buildRBC(std::ofstream &ostream);

    static void printErrMsg(const std::string &message);
};

}  // namespace ast

#endif