#include "ast/method_declaration.h"
using std::size_t;
using std::string;

MethodDeclaration::MethodDeclaration() : Node() {}
MethodDeclaration::MethodDeclaration(std::string t, std::string v) : Node(std::move(t), std::move(v)) {}

/*
 * 1.
 * Create records in the current "Class" scope.
 * Scope add:
 *     Method <name>
 *
 * 2.
 * Get the "Class" record in the "Program" scope.
 * Add methods into "Class".
 *
 * 3.
 * Enter method scope
 * Traverse children.
 *
 * @return: std::nullopt
 */
std::optional<string> MethodDeclaration::generateST() {
    // Create method records
    string method_name, method_type;
    method_type = this->children.at(0)->generateST().value_or("Unknown");
    method_name = this->children.at(1)->generateST().value_or("Unknown");
    std::shared_ptr<Method> method_ptr = std::make_shared<Method>(method_name, method_type);
    MethodDeclaration::st.addRecord(method_name, method_ptr);

    // Add method records into "Class"
    string scope_name = MethodDeclaration::st.getScopeTitle();
    string scope_type = MethodDeclaration::st.getScopeType();
    auto record_ptr = MethodDeclaration::st.lookupRecord(scope_name).value_or(nullptr);
    if (scope_type == "Class" && record_ptr) {
        auto class_ptr = std::dynamic_pointer_cast<STClass>(record_ptr);
        class_ptr->addMethod(method_ptr);
    }

    // Enter method scope
    MethodDeclaration::st.enterScope();
    MethodDeclaration::st.setScopeTitle("Method: " + method_name);
    // "FormalParameterList", "MethodBody"
    for (size_t i = 2; i < this->children.size(); ++i) {
        this->children.at(i)->generateST();
    }
    MethodDeclaration::st.exitScope();  // Exit method scope

    return std::nullopt;
}

std::optional<std::string> MethodDeclaration::checkSemantics() {
    // Enter method scope
    MethodDeclaration::st.enterScope();
    for (auto &child : this->children) {
        if (child->getType() == "MethodBody" || child->getType() == "Return") {
            child->checkSemantics();
        }
    }
    MethodDeclaration::st.exitScope();  // Exit method scope

    return std::nullopt;
}
