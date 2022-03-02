#include "ast/declarations/declarations.h"
using ast::Declarations;
using std::string;

Declarations::Declarations() : Node() {}
Declarations::Declarations(string t, string v) : Node(std::move(t), std::move(v)) {}

/*
 * @brief:
 *   1. reset id before traverse every class
 *   2. Create a BasicBlock ptr as the entry.
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
