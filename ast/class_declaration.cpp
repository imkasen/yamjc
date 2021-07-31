#include "class_declaration.h"
using std::string;
using std::size_t;

ClassDeclaration::ClassDeclaration() : Node() {}

ClassDeclaration::ClassDeclaration(string t, string v) : Node(t, v) {}

/*
 * 1.
 * Create records in the current "Class" scope.
 * Set the scope title.
 * Scope add:
 *     Variable: this
 *
 * 2.
 * Create a Class record in the parent "Program" scope.
 * Parent scope add:
 *     Class: <class name>
 * Add "this" listed above into "Class"
 *
 * 3.
 * Traverse children.
 *
 * @return: std::nullopt
 */
std::optional<string> ClassDeclaration::generateST()
{
    string class_name, class_type;

    // create records to the current scope
    class_name = class_type = this->children.at(0)->generateST().value_or("Unknown");
    ClassDeclaration::st.setScopeTitle("Class: " + class_name); // set the current scope title
    std::shared_ptr<Variable> variable_this_ptr = std::make_shared<Variable>("this", class_type);
    ClassDeclaration::st.addRecord("this", variable_this_ptr);

    // create a class record to the parent scope("Program")
    std::shared_ptr<STClass> class_ptr = std::make_shared<STClass>(class_name, class_type);
    class_ptr->addVariable(variable_this_ptr);
    ClassDeclaration::st.getParentScope()->addRecord(class_name, class_ptr);

    for (size_t i = 1; i < this->children.size(); ++i) // Declarations
    {
        this->children.at(i)->generateST();
    }

    return std::nullopt;
}
