#include "ast/declarations/variable_declaration.h"
using ast::VarDeclaration;
using st::Method;
using st::STClass;
using st::Variable;
using std::string;

/*
       "VarDeclaration"
          /     \
      "Type"  "Identifier"
 */

VarDeclaration::VarDeclaration() : Node() {}
VarDeclaration::VarDeclaration(string t, string v) : Node(std::move(t), std::move(v)) {}

/*
 * @brief:
 *   1. Create "Variable" records in the current "Class" || "Method" scope.
 *      Add into the current scope:
 *          Variable: <variable name>
 *   2. Get the "Class" || "Method" ptr in the "Program" || "Class" scope.
 *      Add "Variable" ptr into "Class" || "Method" ptr.
 * @return: std::nullopt
 */
std::optional<string> VarDeclaration::generateST() {
    // 1.
    string variable_type = this->children.at(0)->generateST().value_or("Unknown");
    string variable_name = this->children.at(1)->generateST().value_or("Unknown");
    std::shared_ptr<Variable> variable_ptr = std::make_shared<Variable>(variable_name, variable_type);
    VarDeclaration::st.addRecord(variable_name, variable_ptr);

    // 2.
    string scope_name = VarDeclaration::st.getScopeTitle();
    string scope_type = VarDeclaration::st.getScopeType();
    auto record_ptr = VarDeclaration::st.lookupRecord(scope_name).value_or(nullptr);  // std::shared_ptr<Record>
    if (scope_type == "Class" && record_ptr) {
        auto class_ptr = std::dynamic_pointer_cast<STClass>(record_ptr);
        class_ptr->addVariable(variable_ptr);
    } else if (scope_type == "Method" && record_ptr) {
        auto method_ptr = std::dynamic_pointer_cast<Method>(record_ptr);
        method_ptr->addVariable(variable_ptr);
    }

    return std::nullopt;
}

/*
 * @brief: Check if a custom "Class" type exists.
 * @return: std::nullopt
 */
std::optional<string> VarDeclaration::checkSemantics() {
    string type_name = this->children.at(0)->checkSemantics().value_or("");
    if (type_name != "int" && type_name != "boolean" && type_name != "int[]") {
        auto c_record_ptr = VarDeclaration::st.lookupRecordInRoot(type_name).value_or(nullptr);
        if (!c_record_ptr) {
            string msg = "[Semantic Analysis] - Error: Class \"" + type_name + "\" does not exist!";
            VarDeclaration::printErrMsg(msg);
        }
    }

    return std::nullopt;
}

/*
 * @brief:
 *   1. Get current "BasicBlock"
 *   2. Create an instruction "IRAssign"
 * @return: std::nullopt
 */
std::optional<IRReturnVal> VarDeclaration::generateIR() {
    // 1.
    std::shared_ptr<cfg::BasicBlock> cur_bb = VarDeclaration::bb_list.back();
    // 2.
    string type, lhs;
    const auto tp_vrt = this->children.at(0)->generateIR().value_or(std::monostate{});
    if (auto ptr = std::get_if<string>(&tp_vrt)) {
        type = *ptr;
    }
    const auto vrt = this->children.at(1)->generateIR().value_or(std::monostate{});
    if (auto ptr = std::get_if<string>(&vrt)) {
        lhs = *ptr;
    }
    // initialize local variables
    std::shared_ptr<cfg::Tac> instruction;
    if (type == "int") {
        instruction = std::make_shared<cfg::IRAssign>("0", lhs, 'i');
    } else if (type == "boolean") {
        instruction = std::make_shared<cfg::IRAssign>("0", lhs, 'b');
    } else if (type == "int[]") {
        instruction = std::make_shared<cfg::IRAssign>("null", lhs, 'a');
    }
    else {  // self-defined class
        instruction = std::make_shared<cfg::IRAssign>("null", lhs, 'r');
    }
    cur_bb->addInstruction(instruction);

    return std::nullopt;
}
