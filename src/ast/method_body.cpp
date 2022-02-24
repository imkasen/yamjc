#include "ast/method_body.h"
using ast::MethodBody;
using std::string;

/*
       "MethodBody"         or   "MethodBody"
            |          \             |
      "VarDeclaration"  ...     "PrintStatement"
 */

MethodBody::MethodBody() : Node() {}
MethodBody::MethodBody(string t, string v) : Node(std::move(t), std::move(v)) {}

/*
 * @brief: Traverse nodes.
 * @return: std::nullopt
 */
std::optional<string> MethodBody::generateST() {
    for (const auto &child : this->children) {
        if (child->getType() == "VarDeclaration") {
            child->generateST();
        }
    }
    return std::nullopt;
}

/*
 * @brief:
 *   1. Create a BasicBlock ptr as the entry, add it into the "cfg_list".
 *   2. Traverse nodes.
 *      If the return value of a child is "BasicBlock" ptr, add it into the entry.
 *      (Although it contains a 'for' loop, there is only one return value actually.)
 * @return: std::nullopt;
 */
std::optional<IRReturnVal> MethodBody::generateIR() {
    // 1.
    std::shared_ptr<cfg::BasicBlock> entry_ptr = std::make_shared<cfg::BasicBlock>();
    MethodBody::cfg_list.push_back(entry_ptr);
    // 2.
    for (const auto &child : this->children) {
        const auto vrt = child->generateIR().value_or(std::monostate{});
        // if contains "BasicBlock" ptr
        if (auto bb_ptr = std::get_if<std::shared_ptr<cfg::BasicBlock>>(&vrt)) {
            entry_ptr->setTrueExit(*bb_ptr);
        }
    }

    return std::nullopt;
}
