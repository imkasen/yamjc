#include "ast/class_declaration.h"
using std::string;
using std::size_t;

ClassDeclaration::ClassDeclaration() : Node() {}
ClassDeclaration::ClassDeclaration(string t, string v) : Node(std::move(t), std::move(v)) {}

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
 * If Class extends Class,
 * Traverse children first,
 * Then copy variables and methods.
 *
 * @return: std::nullopt
 */
std::optional<string> ClassDeclaration::generateST()
{
    // create records to the current scope
    string class_name, class_type;
    class_name = class_type = this->children.at(0)->generateST().value_or("Unknown");
    ClassDeclaration::st.setScopeTitle("Class: " + class_name); // set the current scope title
    std::shared_ptr<Variable> variable_this_ptr = std::make_shared<Variable>("this", class_type);
    ClassDeclaration::st.addRecord("this", variable_this_ptr);

    // create a class record to the parent scope("Program")
    std::shared_ptr<STClass> class_ptr = std::make_shared<STClass>(class_name, class_type);
    class_ptr->addVariable(variable_this_ptr);
    ClassDeclaration::st.getParentScope()->addRecord(class_name, class_ptr);

    // "Class" extends
    if (this->children.at(1)->getType() == "Identifier")
    {
        for (size_t i = 2; i < this->children.size(); ++i) // Declarations
        {
            this->children.at(i)->generateST();
        }

        string parent_class_name = this->children.at(1)->getValue();
        auto c_record_ptr = ClassDeclaration::st.lookupRecord(parent_class_name).value_or(nullptr);
        if (c_record_ptr)
        {
            std::shared_ptr<STClass> parent_class_ptr = std::dynamic_pointer_cast<STClass>(c_record_ptr);

            // deep copy variables in Class
            for (const auto &pair : parent_class_ptr->getVariables())
            {
                if (pair.first != "this" && !ClassDeclaration::st.lookupRecord(pair.first).has_value())
                {
                    std::shared_ptr<Variable> variable_ptr = std::make_shared<Variable>(*(pair.second));
                    ClassDeclaration::st.addRecord(variable_ptr->getName(), variable_ptr);
                    class_ptr->addVariable(variable_ptr);
                }
            }

            // deep copy methods in Class
            for (const auto &pair : parent_class_ptr->getMethods())
            {
                // methods that need to be inherited but not overwritten
                if (!ClassDeclaration::st.lookupChildScope(pair.first).value_or(nullptr))
                {
                    std::shared_ptr<Method> method_ptr = std::make_shared<Method>(*(pair.second));
                    ClassDeclaration::st.addRecord(method_ptr->getName(), method_ptr);
                    class_ptr->addMethod(method_ptr);

                    // enter method scope, generate st only
                    ClassDeclaration::st.enterScope();
                    ClassDeclaration::st.setScopeTitle("Method: " + method_ptr->getName());
                    for (const auto &v_pair : method_ptr->getVariables())
                    {
                        ClassDeclaration::st.addRecord(v_pair.first, v_pair.second);
                    }
                    for (const auto &p_pair : method_ptr->getParameters())
                    {
                        ClassDeclaration::st.addRecord(p_pair.first, p_pair.second);
                    }
                    ClassDeclaration::st.exitScope();
                }
            }
        }
    }
    else // no Class extends
    {
        for (size_t i = 1; i < this->children.size(); ++i) // Declarations
        {
            this->children.at(i)->generateST();
        }
    }

    return std::nullopt;
}
