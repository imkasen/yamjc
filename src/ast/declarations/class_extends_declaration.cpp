#include "ast/declarations/class_extends_declaration.h"
using ast::ClassExtendsDeclaration;
using st::Method;
using st::Parameter;
using st::STClass;
using st::Variable;
using std::string;

/*
              "ClassDeclaration"
             /        |        \
    "Identifier"  "Identifier"  ["Declarations"]
 */

[[maybe_unused]] ClassExtendsDeclaration::ClassExtendsDeclaration(string t, string v) : Node(std::move(t), std::move(v)) {}

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
 *   3. "Class" extends from "Class",
 *      Traverse children first,
 *      Then deep copy "Variables" and "Methods" from father "Class" record.
 *
 * @return: std::nullopt
 */
std::optional<string> ClassExtendsDeclaration::generateST() {
    // 1.
    string class_name, class_type;
    class_name = class_type = this->children.at(0)->generateST().value_or("Unknown");
    ClassExtendsDeclaration::st.setScopeTitle("Class: " + class_name);  // Set the current scope title
    std::shared_ptr<Variable> variable_this_ptr = std::make_shared<Variable>("this", class_type);
    ClassExtendsDeclaration::st.addRecord("this", variable_this_ptr);

    // 2.
    std::shared_ptr<STClass> class_ptr = std::make_shared<STClass>(class_name, class_type);
    class_ptr->addVariable(variable_this_ptr);
    ClassExtendsDeclaration::st.getParentScope()->addRecord(class_name, class_ptr);

    // 3.
    // if "Class" contains nothing
    //    `this->children.size() == 2`
    // else
    //    `this->children.size() >= 3`

    // Traverse "Declarations"
    for (size_t i = 2; i < this->children.size(); ++i) {
        this->children.at(i)->generateST();
    }

    string parent_class_name = this->children.at(1)->generateST().value_or("Unknown");
    // "Type: Class_child Class_parent"
    class_ptr->setType(class_type + " " + parent_class_name);

    auto c_record_ptr = ClassExtendsDeclaration::st.lookupRecord(parent_class_name).value_or(nullptr);
    if (c_record_ptr) {
        std::shared_ptr<STClass> parent_class_ptr = std::dynamic_pointer_cast<STClass>(c_record_ptr);

        // Deep copy "Variables" in "Class"
        for (const auto &[var_name, var_ptr] : parent_class_ptr->getVariables()) {
            if (var_name != "this" && !ClassExtendsDeclaration::st.lookupRecord(var_name).has_value()) {
                std::shared_ptr<Variable> variable_ptr = std::make_shared<Variable>(*(var_ptr));
                ClassExtendsDeclaration::st.addRecord(variable_ptr->getName(), variable_ptr);
                class_ptr->addVariable(variable_ptr);
            }
        }

        // Deep copy "Methods" in "Class"
        for (const auto &[mtd_name, mtd_ptr] : parent_class_ptr->getMethods()) {
            // "Methods" that need to be inherited but not overwritten
            if (!ClassExtendsDeclaration::st.lookupChildScope(mtd_name).value_or(nullptr)) {
                std::shared_ptr<Method> method_ptr =
                    std::make_shared<Method>(mtd_name, mtd_ptr->getType());
                ClassExtendsDeclaration::st.addRecord(method_ptr->getName(), method_ptr);
                class_ptr->addMethod(method_ptr);
                // Enter "Method" scope, deep copy variables and parameters
                ClassExtendsDeclaration::st.enterScope();
                ClassExtendsDeclaration::st.setScopeTitle("Method: " + method_ptr->getName());
                for (const auto &[var_name, var_ptr] : mtd_ptr->getVariables()) {
                    std::shared_ptr<Variable> v_ptr =
                        std::make_shared<Variable>(var_name, var_ptr->getType());
                    method_ptr->addVariable(v_ptr);
                    ClassExtendsDeclaration::st.addRecord(v_ptr->getName(), v_ptr);
                }
                for (const auto &par_ptr : mtd_ptr->getParameters()) {
                    std::shared_ptr<Parameter> p_ptr =
                        std::make_shared<Parameter>(par_ptr->getName(), par_ptr->getType());
                    method_ptr->addParameter(p_ptr);
                    ClassExtendsDeclaration::st.addRecord(p_ptr->getName(), p_ptr);
                }
                ClassExtendsDeclaration::st.exitScope();
            }
        }
    }

    return std::nullopt;
}

/*
 * @brief: Traverse child nodes.
 * @return: std::nullopt
 */
std::optional<string> ClassExtendsDeclaration::checkSemantics() {
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

    return std::nullopt;
}

/*
 * @brief: Traverse child nodes.
 * @return: std::monostate
 */
IRReturnVal ClassExtendsDeclaration::generateIR() {
    //   if "Class" contains nothing
    //      `this->children.size() == 2`
    //   else
    //      `this->children.size() >= 3`
    if (this->children.size() >= 2 && this->children.at(1)->getType() == "Identifier") {
        // Traverse "Declarations"
        for (size_t i = 2; i < this->children.size(); ++i) {
            this->children.at(i)->generateIR();
        }
    }

    return std::monostate {};
}
