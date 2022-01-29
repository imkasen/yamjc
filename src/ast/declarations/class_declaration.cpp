#include "ast/declarations/class_declaration.h"
using std::size_t;
using std::string;

ClassDeclaration::ClassDeclaration() : Declarations() {}
ClassDeclaration::ClassDeclaration(string t, string v) : Declarations(std::move(t), std::move(v)) {}

/*
 *      "ClassDeclaration"
 *         /        \
 * "Identifier"  ["Declarations"]
 *
 * @brief:
 *   1. Create records in the current "Class" scope.
 *      Set the scope title.
 *      Add into the current scope:
 *          Variable: this
 *   2. Create a "Class" record in the parent "Program" scope.
 *      Add "this" record which listed above into "Class" record.
 *      Add into the parent scope:
 *          Class: <name>
 *   3. Traverse children.
 *
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
    // if "Class" contains nothing
    //     `this->children.size() == 1`
    // else
    //     `this->children.size() >= 2`

    // Traverse "Declarations"
    for (size_t i = 1; i < this->children.size(); ++i) {
        this->children.at(i)->generateST();
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
