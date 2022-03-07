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
std::tuple<std::string, std::string> Interpreter::lineSplit(const string &str, const char &delimiter) {
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

void Interpreter::executeCmd(const std::string &lhs, const std::string &rhs) {
    if (lhs.find('L') == 0 && rhs.empty()) {  // Block name, e.g. "L0"
        Interpreter::blk_pos_links.try_emplace(lhs, this->cur_act_ptr->getPC());
    } else if (lhs == "iconst") {
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
    } else if (lhs == "istore") {  // pop a number from "data_stk" and store it into the current "activation" record.
        const auto &val_vrt = Interpreter::data_stk.top().value_or(std::monostate{});
        Interpreter::data_stk.pop();
        if (auto val_ptr = std::get_if<int>(&val_vrt)) {
            int val = *val_ptr;
            this->cur_act_ptr->addLocalVar(rhs, val);
        }
    } else if (lhs == "iload") {  // load from the current "activation", push it into "data_stk"
        const auto &vrt = this->cur_act_ptr->getLocalVar(rhs).value_or(std::monostate{});
        if (auto ptr = std::get_if<int>(&vrt)) {
            int val = *ptr;
            Interpreter::data_stk.push(val);
        }
    } else if (lhs == "invokevirtual" && rhs == "__PRINT__") {  // print
        const auto &val_vrt = Interpreter::data_stk.top().value_or(std::monostate{});
        Interpreter::data_stk.pop();
        if (auto val_ptr = std::get_if<int>(&val_vrt)) {
            int val = *val_ptr;
            std::cout << val << std::endl;
        }
    } else if (lhs == "return" && rhs.empty()) {
        return;
    }
}

// read the bytecode file and execute
void Interpreter::run(const std::string &filename) {
    cur_act_ptr = std::make_shared<Activation>();  // create an activation record

    std::ifstream input_stream;
    input_stream.open(filename, std::ios::in);
    while (!input_stream.eof()) {
        string line;
        std::getline(input_stream, line);
        if (!line.empty()) {
            auto [lhs, rhs] = Interpreter::lineSplit(line, ' ');
            cur_act_ptr->setPC(input_stream.tellg());
            this->executeCmd(lhs, rhs);
        }
    }
    input_stream.close();
}
