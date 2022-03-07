#ifndef SMI_INTERPRETER_H
#define SMI_INTERPRETER_H

#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <unordered_map>
#include "activation_stk.h"
#include "data_stk.h"

// link class, method with "BasicBlock",
// "<class_name, <method_name, entry_block_name>>"
// passed from "ast/node.h"
using BlkLinksType = std::unordered_map<std::string, std::unordered_map<std::string, std::string>>;
// store info which links block name and pos_type
// "<block_name, pos_type>"
using BlkPosType = std::unordered_map<std::string, std::ios::pos_type>;

namespace smi {

class Interpreter {
private:
    inline static DataStk data_stk = DataStk();  // NOLINT
    inline static ActivationStk act_stk = ActivationStk();

    [[maybe_unused]] inline static BlkLinksType blk_links = {};
    inline static BlkPosType blk_pos_links = {};

    std::shared_ptr<Activation> cur_act_ptr;

    static std::tuple<std::string, std::string> lineSplit(const std::string &str, const char &delimiter = ' ');
    static void arithOrLogicCmd(const char &c);
    static void compareCmd(int i);
    void executeCmd(const std::string &lhs, const std::string &rhs);

public:
    Interpreter() = delete;
    explicit Interpreter(const BlkLinksType &links);
    ~Interpreter() = default;

    void run(const std::string &filename = "rbc.class");
};

}  // namespace smi

#endif
