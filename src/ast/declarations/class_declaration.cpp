#include "ast/declarations/class_declaration.h"
using std::size_t;
using std::string;

ClassDeclaration::ClassDeclaration() : Node() {}
ClassDeclaration::ClassDeclaration(string t, string v) : Node(std::move(t), std::move(v)) {}

/*
 * @brief:
 *   1. Create records in the current "Class" scope.
 *      Set the scope title.
 *      Add into the current scope:
 *          Variable: this
 *   2. Create a "Class" record in the parent "Program" scope.
 *      Add "this" record which listed above into "Class" record.
 *      Add into the parent scope:
 *          Class: <name>
 *   3. If "Class" extends from "Class",
 *          Traverse children first,
 *          Then copy "Variables" and "Methods" from father "Class" record.
 *      If no extends,
 *          Traverse children directly.
 * @return: std::nullopt
 */
std::optional<string> ClassDeclaration::generateST() {
    // 1.
    string class_name, class_type;
    class_name = class_type = this->children.at(0)->generateST().value_or("Unknown");
    ClassDeclaration::st.setScopeTitle("Class: " + class_name);  // Set the current scope title
    std::shared_ptr<Variable> variable_this_ptr = std::make_shared<Variable>("this", class_type);
    ClassDeclaration::st.addRecord("this", variable_this_ptr);

    // 2.
    std::shared_ptr<STClass> class_ptr = std::make_shared<STClass>(class_name, class_type);
    class_ptr->addVariable(variable_this_ptr);
    ClassDeclaration::st.getParentScope()->addRecord(class_name, class_ptr);

    // 3.
    // "Class" extends from "Class"
    //   if "Class" contains nothing
    //      `this->children.size() == 2`
    //   else
    //      `this->children.size() >= 3`
    if (this->children.size() >= 2 && this->children.at(1)->getType() == "Identifier") {
        // Traverse "Declarations"
        for (size_t i = 2; i < this->children.size(); ++i) {
            this->children.at(i)->generateST();
        }

        string parent_class_name = this->children.at(1)->getValue();
        // "Type: Class_child Class_parent"
        class_ptr->setType(class_type + " " + parent_class_name);

        auto c_record_ptr = ClassDeclaration::st.lookupRecord(parent_class_name).value_or(nullptr);
        if (c_record_ptr) {
            std::shared_ptr<STClass> parent_class_ptr = std::dynamic_pointer_cast<STClass>(c_record_ptr);

            // Deep copy "Variables" in "Class"
            for (const auto &pair : parent_class_ptr->getVariables()) {
                // "Variables" that need to be inherited but not overwritten
                if (pair.first != "this" && !ClassDeclaration::st.lookupRecord(pair.first).has_value()) {
                    std::shared_ptr<Variable> variable_ptr = std::make_shared<Variable>(*(pair.second));
                    ClassDeclaration::st.addRecord(variable_ptr->getName(), variable_ptr);
                    class_ptr->addVariable(variable_ptr);
                }
            }

            // Deep copy "Methods" in "Class"
            for (const auto &pair : parent_class_ptr->getMethods()) {
                // "Methods" that need to be inherited but not overwritten
                if (!ClassDeclaration::st.lookupChildScope(pair.first).value_or(nullptr)) {
                    std::shared_ptr<Method> method_ptr = std::make_shared<Method>(*(pair.second));
                    ClassDeclaration::st.addRecord(method_ptr->getName(), method_ptr);
                    class_ptr->addMethod(method_ptr);

                    // Enter "Method" scope, generate st only
                    ClassDeclaration::st.enterScope();
                    ClassDeclaration::st.setScopeTitle("Method: " + method_ptr->getName());
                    for (const auto &v_pair : method_ptr->getVariables()) {
                        ClassDeclaration::st.addRecord(v_pair.first, v_pair.second);
                    }
                    for (const auto &p_ptr : method_ptr->getParameters()) {
                        ClassDeclaration::st.addRecord(p_ptr->getName(), p_ptr);
                    }
                    ClassDeclaration::st.exitScope();
                }
            }
        }
    }
    // No "Class" extends
    //   if "Class" contains nothing
    //      `this->children.size() == 1`
    //   else
    //      `this->children.size() >= 2`
    else {
        // Traverse "Declarations"
        for (size_t i = 1; i < this->children.size(); ++i) {
            this->children.at(i)->generateST();
        }
    }

    return std::nullopt;
}

/*
 * @brief: Traverse child nodes.
 * @return: std::nullopt
 */
std::optional<std::string> ClassDeclaration::checkSemantics() {
    // "Class" extends from "Class"
    //   if "Class" contains nothing
    //      `this->children.size() == 2`
    //   else
    //      `this->children.size() >= 3`
    if (this->children.size() >= 2 && this->children.at(1)->getType() == "Identifier") {
        // Traverse "Declarations"
        for (size_t i = 2; i < this->children.size(); ++i) {
            this->children.at(i)->checkSemantics();
        }
    }
    // No "Class" extends
    //   if "Class" contains nothing,
    //      `this->children.size() == 1`
    //   else
    //      `this->children.size() >= 2`
    else {
        // Traverse "Declarations"
        for (size_t i = 1; i < this->children.size(); ++i) {
            this->children.at(i)->checkSemantics();
        }
    }

    return std::nullopt;
}