#include "ast/declarations/declarations.h"
using ast::Declarations;
using std::string;

[[maybe_unused]] Declarations::Declarations(string t, string v) : Node(std::move(t), std::move(v)) {}

/*
 * @brief: Traverse children nodes.
 * @return: std::nullopt
 */
std::optional<string> Declarations::generateST() {
    for (const auto &child : this->children) {
        child->generateST();
    }
    return std::nullopt;
}

/*
 * @brief: Traverse children nodes.
 * @return: std::nullopt
 */
std::optional<string> Declarations::checkSemantics() {
    for (const auto &child : this->children) {
        child->checkSemantics();
    }
    return std::nullopt;
}

/*
 * @brief:
 *   1. reset id before traverse every class
 *   2. Create a BasicBlock ptr as the entry for class, used to store class variable IR.
 *   3. Traverse child nodes
 * @return: std::nullopt
 */
std::optional<IRReturnVal> Declarations::generateIR() {
    // 1.
    cfg::Tac::resetID();
    // 2.
    Declarations::bb_list.push_back(Declarations::createBB());
    // 3.
    for (const auto &child : this->children) {
        child->generateIR();
    }

    return std::nullopt;
}
