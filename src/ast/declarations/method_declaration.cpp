#include "ast/declarations/method_declaration.h"
using ast::MethodDeclaration;
using st::Method;
using st::STClass;
using std::size_t;
using std::string;

/*
                  "MethodDeclaration"
         /          /           \                 \
     "Type"  "Identifier"  ["FormalParameterList"]  "MethodBody"
 */

[[maybe_unused]] MethodDeclaration::MethodDeclaration(std::string t, std::string v) : Node(std::move(t), std::move(v)) {}

/*
 * @brief:
 *   1. Create "Method" records in the current "Class" scope.
 *      Add into the current scope:
 *          Method: <name>
 *   2. Get the "Class" ptr in the "Program" scope.
 *      Add the "Method" ptr into the "Class" ptr.
 *   3. Enter "Method" scope
 *      Traverse children.
 * @return: std::nullopt
 */
std::optional<string> MethodDeclaration::generateST() {
    // 1.
    string method_name, method_type;
    method_type = this->children.at(0)->generateST().value_or("Unknown");
    method_name = this->children.at(1)->generateST().value_or("Unknown");
    std::shared_ptr<Method> method_ptr = std::make_shared<Method>(method_name, method_type);
    MethodDeclaration::st.addRecord(method_name, method_ptr);

    // 2.
    string scope_name = MethodDeclaration::st.getScopeTitle();
    string scope_type = MethodDeclaration::st.getScopeType();
    auto record_ptr = MethodDeclaration::st.lookupRecord(scope_name).value_or(nullptr);
    if (scope_type == "Class" && record_ptr) {
        auto class_ptr = std::dynamic_pointer_cast<STClass>(record_ptr);
        class_ptr->addMethod(method_ptr);
    }

    // 3.
    MethodDeclaration::st.enterScope();  // Enter each "Method" scope
    MethodDeclaration::st.setScopeTitle("Method: " + method_name);
    // Traverse ["FormalParameterList"], "MethodBody"
    for (size_t i = 2; i < this->children.size(); ++i) {
        this->children.at(i)->generateST();
    }
    MethodDeclaration::st.exitScope();  // Exit "Method" scope

    return std::nullopt;
}

/*
 * @brief: Traverse child nodes of "MethodBody" or "Return".
 * @return: std::nullopt
 */
std::optional<string> MethodDeclaration::checkSemantics() {
    MethodDeclaration::st.enterScope();  // Enter "Method" scope
    for (const auto &child : this->children) {
        if (child->getType() == "MethodBody" || child->getType() == "Return") {
            child->checkSemantics();
        }
    }
    MethodDeclaration::st.exitScope();  // Exit "Method" scope

    return std::nullopt;
}

/*
 * @brief:
 *   1. Reset id before traverse every method
 *   2. Create a BasicBlock ptr as the entry.
 *   3. Traverse child nodes
 * @return: std::monostate
 */
IRReturnVal MethodDeclaration::generateIR() {
    MethodDeclaration::st.enterScope();  // Enter "Method" scope

    // 1.
    cfg::Tac::resetID();
    // 2.
    MethodDeclaration::bb_list.push_back(MethodDeclaration::createBB());
    // 3.
    for (const auto &child : this->children) {
        child->generateIR();
    }

    MethodDeclaration::st.exitScope();  // Exit "Method" scope

    return std::monostate {};
}
