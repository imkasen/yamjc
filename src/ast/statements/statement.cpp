#include "ast/statements/statement.h"
using ast::Statement;
using std::string;

Statement::Statement(string t, string v) : Node(std::move(t), std::move(v)) {}

/*
 * @brief: It will not be called at all, do nothing.
 * @return: std::nullopt
 */
std::optional<string> Statement::generateST() {
    return std::nullopt;
}

/*
 * @brief: Traverse children nodes, also used by "ElseStatement".
 * @return: std::nullopt
 */
std::optional<string> Statement::checkSemantics() {
    for (const auto &child : this->children) {
        child->checkSemantics();
    }
    return std::nullopt;
}

/*
 * @brief:
 *   1. "Statement": Traverse child nodes
 *   2. "Statements":
 *       (mainly used for "If-While" nested structure)
 *       Get the returned "BasicBlock" from recursive call.
 *       Set the returned "BasicBlock" as the true exit of last "BasicBlock".
 * @return: std::nulopt
 */
std::optional<IRReturnVal> Statement::generateIR() {
    string type = this->getType();
    // 1.
    if (type == "Statement") {
        for (const auto &child : this->children) {
            child->generateIR();
        }
    }
    // 2.
    else {  // "Statements"
        std::shared_ptr<cfg::BasicBlock> cur_bb = Statement::bb_list.back();
        for (const auto &child : this->children) {
            const auto vrt = child->generateIR().value_or(std::monostate{});
            if (auto ptr = std::get_if<std::shared_ptr<cfg::BasicBlock>>(&vrt)) {
                cur_bb->setTrueExit(*ptr);
                cur_bb = Statement::bb_list.back();
            }
        }
    }
    return std::nullopt;
}
