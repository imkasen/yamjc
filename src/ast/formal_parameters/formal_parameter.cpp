#include "ast/formal_parameters/formal_parameter.h"
using ast::FormalParameter;
using st::Method;
using st::Parameter;
using std::string;

/*
    "FormalParameter"
         /   \
    "Type"  "Identifier"
 */

FormalParameter::FormalParameter() : FormalParameterList() {}
FormalParameter::FormalParameter(string t, string v) : FormalParameterList(std::move(t), std::move(v)) {}

/*
 *@brief:
 *   1. Create "Parameter" records in the current "Method" scope.
 *      Add into the current scope:
 *          Parameter: <parameter name>
 *   2. Get the "Method" ptr in the "Class" scope.
 *      Add "Parameter" ptr into "Method" ptr.
 * @return: std::nullopt
 */
std::optional<string> FormalParameter::generateST() {
    // 1.
    string parameter_type = this->children.at(0)->generateST().value_or("Unknown");
    string parameter_name = this->children.at(1)->generateST().value_or("Unknown");
    std::shared_ptr<Parameter> parameter_ptr = std::make_shared<Parameter>(parameter_name, parameter_type);
    FormalParameter::st.addRecord(parameter_name, parameter_ptr);

    // 2.
    string scope_name = FormalParameter::st.getScopeTitle();
    string scope_type = FormalParameter::st.getScopeType();
    auto record_ptr = FormalParameter::st.lookupRecord(scope_name).value_or(nullptr);
    if (scope_type == "Method" && record_ptr) {
        auto method_ptr = std::dynamic_pointer_cast<Method>(record_ptr);
        method_ptr->addParameter(parameter_ptr);
    }

    return std::nullopt;
}

/*
 * @brief:
 *   1. Get current "BasicBlock"
 *   2. Create an instruction "IRParameter"
 * @return: std::nullopt
 */
std::optional<IRReturnVal> FormalParameter::generateIR() {
    // 1.
    std::shared_ptr<cfg::BasicBlock> cur_bb = FormalParameter::bb_list.back();
    // 2.
    string lhs;
    char type = 0;
    const auto t_vrt = this->children.at(0)->generateIR().value_or(std::monostate{});
    if (auto ptr = std::get_if<string>(&t_vrt)) {
        if (*ptr == "int") {
            type = 'i';
        } else if (*ptr == "boolean"){
            type = 'b';
        } else if (*ptr == "int[]") {
            type = 'a';
        } else { // self-defined class
            type = 'r';
        }
    }
    const auto vrt = this->children.at(1)->generateIR().value_or(std::monostate{});
    if (auto ptr = std::get_if<string>(&vrt)) {
        lhs = *ptr;
    }
    // initialize formal parameters
    std::shared_ptr<cfg::Tac> instruction = std::make_shared<cfg::IRParameter>(lhs, type);
    cur_bb->addInstruction(instruction);

    return std::nullopt;
}
