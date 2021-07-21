#include "main_class.h"
using std::string;

MainClass::MainClass() : Node() {}

MainClass::MainClass(string t, string v) : Node(t, v) {}

/*
 * 1.
 * Create records in the current "Class" scope.
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
 * Enter into a child "Method" scope and create a parameter record.
 * Child scope add:
 *     Variable: <parameter name>
 * Add parameter into "main" Method listed above.
 * Traverse children.
 *
 * @return: string - class name
 */
std::optional<string> MainClass::execute()
{
    string class_name, class_type, parameter_name;

    // create records to the current scope
    class_name = class_type = this->children.at(0).execute().value_or("Unknown");
    std::shared_ptr<Variable> variable_this_ptr = std::make_shared<Variable>("this", class_type); // used as type here
    std::shared_ptr<Method> method_main_ptr = std::make_shared<Method>("main", "void");
    Node::st->addRecord("this", variable_this_ptr);
    Node::st->addRecord("main", method_main_ptr);

    // create a class record to the parent scope("Program")
    std::shared_ptr<STClass> class_ptr = std::make_shared<STClass>(class_name, "int");
    class_ptr->addVariable(variable_this_ptr);
    class_ptr->addMethod(method_main_ptr);
    Node::st->getParentScope()->addRecord(class_name, class_ptr);

    // enter the method scope
    Node::st->enterScope();
    Node::st->setScopeTitle("Method:main");
    parameter_name = this->children.at(1).execute().value_or("Unknown");
    std::shared_ptr<Variable> variable_parameter_ptr = std::make_shared<Variable>(parameter_name, "String[]");
    method_main_ptr->addParameter(variable_parameter_ptr);
    Node::st->addRecord(parameter_name, variable_parameter_ptr);
    for (size_t i = 2; i < this->children.size(); ++i) // MethodBody
    {
        this->children.at(i).execute();
    }
    Node::st->exitScope(); // exit method scope

    return class_name;
}
