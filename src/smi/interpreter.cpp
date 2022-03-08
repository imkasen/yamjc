#include "interpreter.h"
using smi::Interpreter;
using std::string;

Interpreter::Interpreter(const BlkLinksType &links) {
    Interpreter::blk_links = links;
    this->cur_act_ptr = nullptr;
}

/*
 * @brief:
 *   split one line
 *   e.g. "L0" -> {"L0", ""}
 *        "iconst 10" -> {"iconst", "10"}
 *        ...
 * @return: tuple
 */
std::tuple<std::string, std::string> Interpreter::strSplit(const string &str, const char &delimiter) {
    string lhs, rhs;
    if (std::size_t idx; (idx = str.find(delimiter)) != string::npos) {
        lhs = str.substr(0, idx);
        rhs = str.substr(idx + 1);
    } else {
        lhs = str;
    }
    return {lhs, rhs};
}

/*
 * @brief:
 *   arithmetic or logic calculation
 *   pop 2 numbers from "data_stk",
 *   do +, -, *, /, &, |, ^
 *   push back to "data_stk"
 */
void Interpreter::arithOrLogicCmd(const char &c) {
    const auto &b_vrt = Interpreter::data_stk.top().value_or(std::monostate{});
    Interpreter::data_stk.pop();
    const auto &a_vrt = Interpreter::data_stk.top().value_or(std::monostate{});
    Interpreter::data_stk.pop();

    auto b_ptr = std::get_if<int>(&b_vrt);
    auto a_ptr = std::get_if<int>(&a_vrt);

    if (a_ptr && b_ptr) {
        int a = *a_ptr;
        int b = *b_ptr;
        switch (c) {
            case '+':
                Interpreter::data_stk.push(a + b);
                break;
            case '-':
                Interpreter::data_stk.push(a - b);
                break;
            case '*':
                Interpreter::data_stk.push(a * b);
                break;
            case '/':
                Interpreter::data_stk.push(a / b);
                break;
            case '&':
                Interpreter::data_stk.push(a & b);
                break;
            case '|':
                Interpreter::data_stk.push(a | b);
                break;
            case '^':
                Interpreter::data_stk.push(a ^ b);
                break;
            default:
                break;
        }
    }
}

/*
 * @brief:
 *   compare calculation
 *   pop 2 numbers from "data_stk",
 *   do ==, !=, >, >=, <, <=
 *   push back to "data_stk"
 */
void Interpreter::compareCmd(int i) {
    // 0: ==, 1: !=, 2: >, 3: >=, 4: <, 5: <=
    enum {eq, ne, gt, ge, lt, le};

    const auto &b_vrt = Interpreter::data_stk.top().value_or(std::monostate{});
    Interpreter::data_stk.pop();
    const auto &a_vrt = Interpreter::data_stk.top().value_or(std::monostate{});
    Interpreter::data_stk.pop();

    auto b_ptr = std::get_if<int>(&b_vrt);
    auto a_ptr = std::get_if<int>(&a_vrt);

    if (a_ptr && b_ptr) {
        int a = *a_ptr;
        int b = *b_ptr;

        switch (i) {
            case eq:
                Interpreter::data_stk.push(a == b);
                break;
            case ne:
                Interpreter::data_stk.push(a != b);
                break;
            case gt:
                Interpreter::data_stk.push(a > b);
                break;
            case ge:
                Interpreter::data_stk.push(a >= b);
                break;
            case lt:
                Interpreter::data_stk.push(a < b);
                break;
            case le:
                Interpreter::data_stk.push(a <= b);
                break;
            default:
                break;
        }
    }
}

/*
 * @brief: execute "invokevirtual" instruction
 */
void Interpreter::methodCallCmd(const string &rhs) {
    if (rhs == "__PRINT__") {  // print
        const auto &val_vrt = Interpreter::data_stk.top().value_or(std::monostate{});
        Interpreter::data_stk.pop();
        if (auto val_ptr = std::get_if<int>(&val_vrt)) {
            int val = *val_ptr;
            std::cout << val << std::endl;
        }
    } else {  // method call, go to the corresponding "BasicBlock"
        // get class name and method name inorder to get block name
        string blk_name;
        auto [cls_var_name, mtd_name] = Interpreter::strSplit(rhs, '.');
        if (cls_var_name.find("_r") != string::npos) {  // e.g. "_r0.Sum"
            const auto &cls_var_vrt = this->cur_act_ptr->getLocalVar(cls_var_name).value_or(std::monostate{});
            if (auto ptr = std::get_if<string>(&cls_var_vrt)) {
                string cls_name = *ptr;
                blk_name = Interpreter::blk_links.at(cls_name).at(mtd_name);  // get block name
            }
        } else {  // e.g. "Test.Sum"
            blk_name = Interpreter::blk_links.at(cls_var_name).at(mtd_name);
        }

        if (!blk_name.empty()) {
            // push current activation record and create a new record
            Interpreter::act_stk.push(this->cur_act_ptr);
            this->cur_act_ptr = std::make_shared<Activation>();
            this->gotoCmd(blk_name);
        }
    }
}

/*
 * @brief: go to the specific block
 */
void Interpreter::gotoCmd(const std::string &block_name) {
    // block has been reached before
    if (Interpreter::blk_pos_links.find(block_name) != Interpreter::blk_pos_links.end()) {
        this->input_stream.seekg(Interpreter::blk_pos_links.at(block_name));
    } else {  // block has not been reached yet
        string line;
        // keep moving until reaching the right block
        while (!this->input_stream.eof() && line != block_name) {
            std::getline(this->input_stream, line);
            if (line.find('L') == 0) {
                Interpreter::blk_pos_links.try_emplace(line, this->input_stream.tellg());
            }
        }
    }
}

void Interpreter::executeCmd(const std::string &lhs, const std::string &rhs) {
    if (lhs == "iconst" && !rhs.empty()) {
        Interpreter::data_stk.push(std::stoi(rhs));
    } else if (lhs == "iadd" && rhs.empty()) {
        Interpreter::arithOrLogicCmd('+');
    } else if (lhs == "isub" && rhs.empty()) {
        Interpreter::arithOrLogicCmd('-');
    } else if (lhs == "imul" && rhs.empty()) {
        Interpreter::arithOrLogicCmd('*');
    } else if (lhs == "idiv" && rhs.empty()) {
        Interpreter::arithOrLogicCmd('/');
    } else if (lhs == "iand" && rhs.empty()) {
        Interpreter::arithOrLogicCmd('&');
    } else if (lhs == "ior" && rhs.empty()) {
        Interpreter::arithOrLogicCmd('|');
    } else if (lhs == "ixor" && rhs.empty()) {
        Interpreter::arithOrLogicCmd('^');
    } else if (lhs == "ineg" && rhs.empty()) {
        const auto &vrt = Interpreter::data_stk.top().value_or(std::monostate{});
        Interpreter::data_stk.pop();
        if (auto ptr = std::get_if<int>(&vrt)) {
            int val = *ptr;
            Interpreter::data_stk.push(-val);
        }
    } else if (lhs == "if_icmpeq" && rhs.empty()) {
        Interpreter::compareCmd(0);
    } else if (lhs == "if_icmpne" && rhs.empty()) {
        Interpreter::compareCmd(1);
    } else if (lhs == "if_icmpgt" && rhs.empty()) {
        Interpreter::compareCmd(2);
    } else if (lhs == "if_icmpge" && rhs.empty()) {
        Interpreter::compareCmd(3);
    } else if (lhs == "if_icmplt" && rhs.empty()) {
        Interpreter::compareCmd(4);
    } else if (lhs == "if_icmple" && rhs.empty()) {
        Interpreter::compareCmd(5);
    } else if (lhs == "ifeq" && rhs.empty()) {
        const auto &vrt = Interpreter::data_stk.top().value_or(std::monostate{});
        Interpreter::data_stk.pop();
        if (auto ptr = std::get_if<int>(&vrt)) {
            int val = *ptr;
            if (val != 0) {  // if true, jump over "goto Lx"
                string dump;
                std::getline(this->input_stream, dump);
            }
        }
    } else if (lhs == "istore" && !rhs.empty()) {  // pop a number from "data_stk" and store it into the current "activation" record
        const auto &val_vrt = Interpreter::data_stk.top().value_or(std::monostate{});
        Interpreter::data_stk.pop();
        if (auto val_ptr = std::get_if<int>(&val_vrt)) {
            int val = *val_ptr;
            this->cur_act_ptr->addLocalVar(rhs, val);
        }
    } else if (lhs == "iload" && !rhs.empty()) {  // load from the current "activation", push it into "data_stk"
        const auto &vrt = this->cur_act_ptr->getLocalVar(rhs).value_or(std::monostate{});
        if (auto ptr = std::get_if<int>(&vrt)) {
            int val = *ptr;
            Interpreter::data_stk.push(val);
        }
    } else if (lhs == "new" && !rhs.empty()) {  // e.g. "new Test"
        Interpreter::data_stk.push(rhs);
    } else if (lhs == "astore" && !rhs.empty()) {  // pop a string from "data_stk" and store it into the current "activation" record.
        const auto &vrt = Interpreter::data_stk.top().value_or(std::monostate{});
        Interpreter::data_stk.pop();
        if (auto ptr = std::get_if<string>(&vrt)) {
            string val = *ptr;
            this->cur_act_ptr->addLocalVar(rhs, val);
        }
    } else if (lhs == "invokevirtual" && !rhs.empty()) {
        this->methodCallCmd(rhs);
    } else if (lhs == "goto" && !rhs.empty()) {
        this->gotoCmd(rhs);
    } else if (lhs == "ireturn" && rhs.empty()) {
        this->cur_act_ptr = Interpreter::act_stk.top().value_or(nullptr);
        Interpreter::act_stk.pop();
        if (this->cur_act_ptr) {
            this->input_stream.seekg(this->cur_act_ptr->getPC());
        }
    } else if (lhs == "return" && rhs.empty()) {
        if (Interpreter::data_stk.size() == 0 && Interpreter::act_stk.size() == 0) {
            this->input_stream.close();
        } else {
            return;
        }
    }
}

// read the bytecode file and execute
void Interpreter::run(const std::string &filename) {
    cur_act_ptr = std::make_shared<Activation>();  // create an activation record

    this->input_stream.open(filename, std::ios::in);
    while (!this->input_stream.eof()) {
        string line;
        std::getline(this->input_stream, line);
        cur_act_ptr->setPC(this->input_stream.tellg());
        if (line.find('L') == 0) {  // block name, e.g. "L0"
            Interpreter::blk_pos_links.try_emplace(line, this->input_stream.tellg());
        } else if (!line.empty()) {
            auto [lhs, rhs] = Interpreter::strSplit(line, ' ');
            this->executeCmd(lhs, rhs);
        }
    }
    this->input_stream.close();
}
