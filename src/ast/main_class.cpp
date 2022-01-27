#include "ast/main_class.h"
using std::size_t;
using std::string;

MainClass::MainClass() : Node() {}
MainClass::MainClass(string t, string v) : Node(std::move(t), std::move(v)) {}

/*
 *                 "MainClass"
 *             /       |        \
 *  "Identifier"  "Identifier"  "MethodBody"
 *
 * @brief:
 *   1. Create records in the current "Class" scope.
 *      Set the scope title.
 *      Add into the current scope:
 *          Variable: this
 *          Method: main
 *   2. Create a "Class" record in the parent "Program" scope.
 *      Add "this" and "main" records which listed above into "Class" record.
 *      Add into the parent scope:
 *          Class: <name>
 *   3. Enter into the child "Method" scope and create a "Parameter" record.
 *      Set the child scope title.
 *      Add "parameter" into "main" Method listed above.
 *      Add into the child scope:
 *          Variable: <parameter name>
 *      Traverse children nodes.
 * @return: std::nullopt
 */
std::optional<string> MainClass::generateST() {
    // 1.
    string class_name, class_type;
    class_name = class_type = this->children.at(0)->generateST().value_or("Unknown");
    if ("Unknown" == class_name) {
        string msg = "[Symbol Table Generation] - Error: Could not get the name of main class!";
        MainClass::printErrMsg(msg);
    }
    MainClass::st.setScopeTitle("Class: " + class_name);  // Set the current scope title
    // Used as type here
    std::shared_ptr<Variable> variable_this_ptr = std::make_shared<Variable>("this", class_type);
    // "main" and "void" written below are grammar-restricted.
    std::shared_ptr<Method> method_main_ptr = std::make_shared<Method>("main", "void");
    MainClass::st.addRecord("this", variable_this_ptr);
    MainClass::st.addRecord("main", method_main_ptr);

    // 2.
    std::shared_ptr<STClass> class_ptr = std::make_shared<STClass>(class_name, class_type);
    class_ptr->addVariable(variable_this_ptr);
    class_ptr->addMethod(method_main_ptr);
    MainClass::st.getParentScope()->addRecord(class_name, class_ptr);

    // 3.
    MainClass::st.enterScope();  // Enter each "Method" scope
    // "Method: main" is grammar-restricted.
    MainClass::st.setScopeTitle("Method: main");  // Set the child scope title
    string parameter_name = this->children.at(1)->generateST().value_or("Unknown");
    if ("Unknown" == parameter_name) {
        string msg = "[Symbol Table Generation] - Error: Could not get the parameter name of main method!";
        MainClass::printErrMsg(msg);
    }
    // "String[]" is grammar-restricted.
    std::shared_ptr<Parameter> parameter_ptr = std::make_shared<Parameter>(parameter_name, "String[]");
    method_main_ptr->addParameter(parameter_ptr);
    MainClass::st.addRecord(parameter_name, parameter_ptr);
    // Traverse "MethodBody"
    for (size_t i = 2; i < this->children.size(); ++i) {
        this->children.at(i)->generateST();
    }
    MainClass::st.exitScope();  // Exit "Method" scope

    return std::nullopt;
}

/*
 * @brief: Traverse children nodes of "MethodBody"
 * @return: std::nullopt
 */
std::optional<std::string> MainClass::checkSemantics() {
    MainClass::st.enterScope();  // Enter "Method" scope
    for (size_t i = 2; i < this->children.size(); ++i) {
        this->children.at(i)->checkSemantics();
    }
    MainClass::st.exitScope();   // Exit "Method" scope
    return std::nullopt;
}
