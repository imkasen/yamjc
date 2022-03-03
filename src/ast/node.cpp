#include "ast/node.h"
using ast::Node;
using std::cout;
using std::endl;
using std::size_t;
using std::string;

Node::Node() {
    // Bison needs this
    this->type = "uninitialised";
    this->value = "uninitialised";
}

Node::Node(string t, string v) : type(std::move(t)), value(std::move(v)) {}

void Node::setId(size_t _id) {
    this->id = _id;
}

void Node::setType(string _type) {
    this->type = std::move(_type);
}

void Node::setValue(string _value) {
    this->value = std::move(_value);
}

size_t Node::getId() const {
    return this->id;
}

string Node::getType() const {
    return this->type;
}

string Node::getValue() const {
    return this->value;
}

// Print ast in the command line.
/*
void Node::printAST(size_t depth) {
    for (size_t i = 0; i < depth; ++i) {
        cout << "  ";
    }
    cout << this->getType() << ":" << this->getValue() << endl;
    for (auto i = this->children.begin(); i != this->children.end(); ++i) {
        (*i)->printAST(depth + 1);
    }
}
*/

// Save ast in "ast.txt"
/*
void Node::saveAST(std::ofstream &ostream, size_t depth) {  // NOLINT
    for (size_t i = 0; i < depth; ++i) {
        ostream << "  ";
    }
    ostream << this->getType() << ":" << this->getValue() << endl;
    for (const auto &child : this->children) {
        child->saveAST(ostream, depth + 1);
    }
}
*/

// Generate ast in "ast.dot"
void Node::generateAST(std::ofstream &ostream, size_t &count) {  // NOLINT
    this->setId(count++);
    if (!this->getValue().empty()) {
        ostream << "n" << this->getId() << " [label=\"" << this->getType() << ":" << this->getValue() << "\"];"
                   << endl;
    } else {
        ostream << "n" << this->getId() << " [label=\"" << this->getType() << "\"];" << endl;
    }
    for (const auto &child : this->children) {
        child->generateAST(ostream, count);
        ostream << "n" << this->getId() << " -> n" << child->getId() << ";" << endl;
    }
}

// Generate the symbol table
void Node::buildST(std::ofstream &ostream) {
    this->generateST();
    Node::st.resetTable();
    // Generate "st.dot"
    Node::st.printST(ostream);
}

/*
 * Default behavior for nodes:
 * "Declarations", "FormalParameterList"
 *
 * All abstract syntax trees start with node "Goal",
 * review "parser.yy" for more details.
 *
 * @brief: Traverse children nodes.
 * @return: std::nullopt
 */
std::optional<string> Node::generateST() {  // NOLINT
    for (const auto &child : this->children) {
        child->generateST();
    }
    return std::nullopt;
}

// Check semantic analysis
void Node::semanticAnalysis() {
    this->checkSemantics();
    Node::st.resetTable();
}

/*
 * Default behavior,
 * this behavior is used by following nodes:
 * "MethodBody", "Declarations", "Statement", "ElseStatement"
 *
 * @brief: Traverse children nodes.
 * @return: std::nullopt
 */
std::optional<string> Node::checkSemantics() {  // NOLINT
    for (const auto &child : this->children) {
        child->checkSemantics();
    }
    return std::nullopt;
}

// Generate CFG
void Node::buildCFG(std::ofstream &ostream) {
    this->generateIR();
    Node::st.resetTable();
    // Generate "cfg.dot"
    for (const auto &cfg_ptr : Node::bb_list) {
        ostream << cfg_ptr->printInfo() << endl;
    }
}

/*
 * Default behavior for nodes:
 * "FormalParameterList", "Type"
 *
 * All abstract syntax trees start with node "Goal",
 * review "parser.yy" for more details.
 *
 * @brief: Traverse children nodes.
 * @return: std::nullopt
 */
std::optional<IRReturnVal> Node::generateIR() {  // NOLINT
    for (const auto &child : this->children) {
        child->generateIR();
    }
    return std::nullopt;
}

/*
 * @brief: Create a "BasicBlock", if this "BasicBlock" is an entry, add it into the "blk_links".
 * @return: "BasicBlock" ptr
 */
std::shared_ptr<cfg::BasicBlock> Node::createBB() {
    std::shared_ptr<cfg::BasicBlock> ptr = std::make_shared<cfg::BasicBlock>();
    string method_name, class_name, cur_type = Node::st.getScopeType();
    if (cur_type == "Method") {
        method_name = Node::st.getScopeTitle();
        class_name = Node::st.getParentScope()->getScopeTitle();
    } else if (cur_type == "Class") {
        method_name = "this";
        class_name = Node::st.getScopeTitle();
    }
    Node::blk_links[class_name].try_emplace(method_name, ptr->getName());
    return ptr;
}

/*
 * Generate some simplified readable Java bytecode
 * Referenced from real instructions, but only similar, not the same.
 *
 * Ref: https://en.wikipedia.org/wiki/List_of_Java_bytecode_instructions
 */
void Node::buildRBC(std::ofstream &ostream) {
    for (const auto &cfg_ptr : Node::bb_list) {
        ostream << cfg_ptr->printBC() << endl;
    }
}

void Node::printErrMsg(const string &message) {
    std::cerr << message << endl;
    std::exit(EXIT_FAILURE);
}
