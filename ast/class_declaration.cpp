#include "class_declaration.h"
using std::string;

ClassDeclaration::ClassDeclaration() : Node() {}

ClassDeclaration::ClassDeclaration(string t, string v) : Node(t, v) {}

/*
 * @return: string - class name
 */
std::optional<string> ClassDeclaration::generateST()
{
    string class_name, class_type;

    // create records to the current scope
    class_name = class_type = this->children.at(0).generateST().value_or("Unknown");
    std::shared_ptr<Variable> variable_this_ptr = std::make_shared<Variable>("this", class_type);
    Node::st->addRecord("this", variable_this_ptr);
    for (size_t i = 1; i < this->children.size(); ++i) // Declarations
    {
        this->children.at(i).generateST();
    }

    // create a class record to the parent scope("Program")
    std::shared_ptr<STClass> class_ptr = std::make_shared<STClass>(class_name, class_type);
    class_ptr->addVariable(variable_this_ptr);
    Node::st->getParentScope()->addRecord(class_name, class_ptr);

    return class_name;
}
