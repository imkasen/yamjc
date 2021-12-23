#include "ast/main_class.h"
using std::size_t;
using std::string;

MainClass::MainClass() : Node() {}
MainClass::MainClass(string t, string v) : Node(std::move(t), std::move(v)) {}

/*
 * 1.
 * Create records in the current "Class" scope.
 * Set the scope title.
 * Scope add:
 *     Variable: this
 *     Method: main
 *
 * 2.
 * Create a Class record in the parent "Program" scope.
 * Parent scope add:
 *     Class: <class name>
 * Add "this" and "main" listed above into "Class"
 *
 * 3.
 * Enter into the child "Method" scope and create a parameter record.
 * Set the child scope title.
 * Child scope add:
 *     Variable: <parameter name>
 * Add parameter into "main" Method listed above.
 * Traverse children.
 *
 * @return: std::nullopt
 */
std::optional<string> MainClass::generateST() {
    // Create records to the current scope
    string class_name, class_type;
    class_name = class_type = this->children.at(0)->generateST().value_or("Unknown");
    MainClass::st.setScopeTitle("Class: " + class_name);  // Set the current scope title
    std::shared_ptr<Variable> variable_this_ptr = std::make_shared<Variable>("this", class_type);  // Used as type here
    std::shared_ptr<Method> method_main_ptr = std::make_shared<Method>("main", "void");
    MainClass::st.addRecord("this", variable_this_ptr);
    MainClass::st.addRecord("main", method_main_ptr);

    // Create a class record to the parent scope("Program")
    std::shared_ptr<STClass> class_ptr = std::make_shared<STClass>(class_name, "int");
    class_ptr->addVariable(variable_this_ptr);
    class_ptr->addMethod(method_main_ptr);
    MainClass::st.getParentScope()->addRecord(class_name, class_ptr);

    // Enter the method scope
    MainClass::st.enterScope();
    MainClass::st.setScopeTitle("Method: main");  // Set the child scope title
    string parameter_name = this->children.at(1)->generateST().value_or("Unknown");
    std::shared_ptr<Parameter> variable_parameter_ptr = std::make_shared<Parameter>(parameter_name, "String[]");
    method_main_ptr->addParameter(variable_parameter_ptr);
    MainClass::st.addRecord(parameter_name, variable_parameter_ptr);
    // "MethodBody"
    for (size_t i = 2; i < this->children.size(); ++i) {
        this->children.at(i)->generateST();
    }
    MainClass::st.exitScope();  // Exit method scope

    return std::nullopt;
}

std::optional<std::string> MainClass::checkSemantics() {
    // Enter method scope
    MainClass::st.enterScope();
    // "MethodBody"
    for (size_t i = 2; i < this->children.size(); ++i) {
        this->children.at(i)->checkSemantics();
    }
    MainClass::st.exitScope();
    return std::nullopt;
}
