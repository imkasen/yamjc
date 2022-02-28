#include "ast/expressions/expression.h"
using ast::Expression;
using st::Method;
using st::Record;
using st::STClass;
using std::size_t;
using std::string;

/*
         "Expression"
               |
       "PrimaryExpression"

          "Expression"       or   "Expression"          or    "Expression"
               |                        |                            |
         "AllocExpression"       "ArrayAllocExpression"       "UnaryExpression"

      "Expression"   or  "Expression"    or   "Expression"
          |                   |                   |
        "int"             "boolean"          "keyword:this"

                     "Expression"
                /           |          \
       "AllocExpression"  "Identifier"  "ExpressionList"

                        "Expression"
                /              |         \
      "PrimaryExpression"  "Identifier"  ["ExpressionList"]

                   "Expression"
               /        |           \
      "keyword:this"  "Identifier"  ["ExpressionList"]
 */

Expression::Expression() : Node() {}
Expression::Expression(string t, string v) : Node(std::move(t), std::move(v)) {}

/*
 * @brief: It will not be called at all, do nothing.
 * @return: std::nullopt
 */
std::optional<string> Expression::generateST() {
    return std::nullopt;
}

/*
 * @return: std::nullopt || string
 */
std::optional<string> Expression::checkSemantics() {
    string class_name;
    string method_name;
    string var_name;
    std::shared_ptr<Record> c_record_ptr;
    std::shared_ptr<Record> v_record_ptr;
    std::shared_ptr<Record> m_record_ptr;
    std::shared_ptr<STClass> class_ptr;

    size_t size = this->children.size();
    string type = this->children.at(0)->getType();

    // 1.
    // "Expression" -> "PrimaryExpression"
    if (size == 1 && type == "PrimaryExpression") {
        // Check parameters
        var_name = this->children.at(0)->checkSemantics().value_or("");
        if (var_name == "int" || var_name == "boolean") {
            return var_name;
        }
        v_record_ptr = Expression::st.lookupRecord(var_name).value_or(nullptr);
        if (v_record_ptr && (v_record_ptr->getRecord() == "Variable" || v_record_ptr->getRecord() == "Parameter")) {
            return v_record_ptr->getType();
        } else {
            string msg = "[Semantic Analysis] - Error: Variable \"" + var_name + "\" does not exist in scope \"" +
                         Expression::st.getScopeTitle() + "\"!";
            Expression::printErrMsg(msg);
        }
    }
    // 2.
    // "Expression" -> "AllocExpression"
    // "Expression" -> "ArrayAllocExpression"
    // "Expression" -> "UnaryExpression"
    else if (size == 1 && (type == "AllocExpression" || type == "ArrayAllocExpression" || type == "UnaryExpression")) {
        return this->children.at(0)->checkSemantics();
    }
    // 3.
    // "Expression" -> "int"
    // "Expression" -> "boolean"
    // "Expression" -> "keyword:this"
    else if (size == 1) {
        if (type == "keyword") {
            v_record_ptr = Expression::st.lookupRecord(this->children.at(0)->getValue()).value_or(nullptr);
            if (v_record_ptr) {
                return v_record_ptr->getType();
            }
        }
        // type == "int" || type == "boolean"
        else {
            return type;
        }
    }
    // 4.
    // "Expression" -> "AllocExpression", "Identifier", "ExpressionList"
    else if (size <= 3 && type == "AllocExpression") {
        class_name = this->children.at(0)->checkSemantics().value_or("");  // return class type actually
        method_name = this->children.at(1)->checkSemantics().value_or("");

        c_record_ptr = Expression::st.lookupRecordInRoot(class_name).value_or(nullptr);
        class_ptr = std::dynamic_pointer_cast<STClass>(c_record_ptr);

        m_record_ptr = class_ptr->lookupMethod(method_name).value_or(nullptr);
        if (!m_record_ptr) {
            string msg = "[Semantic Analysis] - Error: Method \"" + method_name + "\" does not exist in scope \"" +
                         class_ptr->getType() + "\"!";
            Expression::printErrMsg(msg);
        }

        this->checkParameters(m_record_ptr);

        return m_record_ptr->getType();
    }
    // 5.
    // "Expression" -> "PrimaryExpression", "Identifier"
    // "Expression" -> "PrimaryExpression", "Identifier", "ExpressionList"
    else if (size <= 3 && type == "PrimaryExpression") {
        var_name = this->children.at(0)->checkSemantics().value_or("");
        method_name = this->children.at(1)->checkSemantics().value_or("");

        v_record_ptr = Expression::st.lookupRecord(var_name).value_or(nullptr);
        if (!v_record_ptr) {
            string msg = "[Semantic Analysis] - Error: Variable \"" + var_name + "\" does not exist in scope \"" +
                         Expression::st.getScopeTitle() + "\"!";
            Expression::printErrMsg(msg);
        }

        class_name = v_record_ptr->getType();
        c_record_ptr = Expression::st.lookupRecordInRoot(class_name).value_or(nullptr);
        class_ptr = std::dynamic_pointer_cast<STClass>(c_record_ptr);

        if (!class_ptr) {
            string msg = "[Semantic Analysis] - Error: Class \"" + class_name + "\" does not exist!";
            Expression::printErrMsg(msg);
        } else {
            m_record_ptr = class_ptr->lookupMethod(method_name).value_or(nullptr);
            if (!m_record_ptr) {
                string msg = "[Semantic Analysis] - Error: Method \"" + method_name + "\" does not exist in scope \"" +
                             Expression::st.getScopeTitle() + "\"!";
                Expression::printErrMsg(msg);
            }
        }

        this->checkParameters(m_record_ptr);

        return m_record_ptr->getType();
    }
    // 6.
    // "Expression" -> "keyword:this", "Identifier"
    // "Expression" -> "keyword:this", "Identifier", "ExpressionList"
    else if (size <= 3 && type == "keyword") {
        method_name = this->children.at(1)->checkSemantics().value_or("");
        m_record_ptr = Expression::st.lookupRecord(method_name).value_or(nullptr);
        if (!m_record_ptr) {
            string msg = "[Semantic Analysis] - Error: Method \"" + method_name + "\" does not exist in scope \"" +
                         Expression::st.getScopeTitle() + "\"!";
            Expression::printErrMsg(msg);
        }

        this->checkParameters(m_record_ptr);

        return m_record_ptr->getType();
    }

    return std::nullopt;
}

/*
 * @brief: Check whether formal parameters meet the syntax requirements, e.g. order, number...
 * @return: Boolean
 */
void Expression::checkParameters(const std::shared_ptr<Record> &m_record_ptr) {
    std::shared_ptr<Method> method_ptr;
    std::deque<string> p_deque;

    if (this->children.size() == 3 && this->children.at(2)->getType() == "ExpressionList") {
        method_ptr = std::dynamic_pointer_cast<Method>(m_record_ptr);

        string parameter_type_list = this->children.at(2)->checkSemantics().value_or("");
        // Split string
        Expression::strSplit(p_deque, parameter_type_list, " ");

        // check number
        if (p_deque.size() != method_ptr->getParameters().size()) {
            string msg = "[Semantic Analysis] - Error: Parameter numbers do not match in scope \"" +
                         Expression::st.getScopeTitle() + "\"!";
            Expression::printErrMsg(msg);
        }

        // check order
        for (size_t i = 0; i < method_ptr->getParameters().size(); ++i) {
            string type_from_m = method_ptr->getParameters().at(i)->getType();
            string type_from_p = p_deque.at(i);

            if (type_from_p != type_from_m) {
                auto c_record_ptr = Expression::st.lookupRecordInRoot(type_from_p).value_or(nullptr);
                /*
                if (c_record_ptr) {
                    string c_record_ptr_type = c_record_ptr->getType();
                    // "Class" extends "Class" situation
                    // e.g. Visitor = Visitor Parent_Visitor
                    // warning: not a rigorous judgment...
                    if (c_record_ptr_type.find(type_from_m) != string::npos) {
                        return;
                    }
                }
                print error
                */

                if (!c_record_ptr || c_record_ptr->getType().find(type_from_m) == string::npos) {
                    string msg = "[Semantic Analysis] - Error: Parameter types (\"";
                    msg += type_from_m + "\" - \"";
                    msg += type_from_p + "\") do not match in scope \"";
                    msg += Expression::st.getScopeTitle() + "\"!";
                    Expression::printErrMsg(msg);
                }
            }
        }
    }
}

void Expression::strSplit(std::deque<std::string> &deque, std::string &text, const std::string &delimiter) {
    size_t pos;

    // string is not end with the delimiter
    if (text.rfind(delimiter) != (text.length() - delimiter.length())) {
        text += delimiter;
    }

    while ((pos = text.find(delimiter)) != string::npos) {
        deque.push_back(text.substr(0, pos));
        text.erase(0, pos + delimiter.length());
    }
}

/*
 * @return: std::nullopt || IRReturnVal
 */
std::optional<IRReturnVal> Expression::generateIR() {
    size_t size = this->children.size();
    string type = this->children.at(0)->getType();
    std::shared_ptr<cfg::BasicBlock> cur_bb = Expression::bb_list.back();
    // "Expression" -> "int"
    // "Expression" -> "boolean"
    // "Expression" -> "PrimaryExpression"
    if (size == 1) {
        return this->children.at(0)->generateIR();
    }
    // "Expression" -> "AllocExpression", "Identifier", "ExpressionList"
    else if (size <= 3 && type == "AllocExpression") {
        string tmp_name, lhs, n;
        // "AllocExpression:new"
        // Get the return value of tmp name
        const auto par_vrt = this->children.at(0)->generateIR().value_or(std::monostate {});
        if (auto s_ptr = std::get_if<string>(&par_vrt)) {
            tmp_name = *s_ptr;
        }
        // "Identifier"
        const auto lhs_vrt = this->children.at(1)->generateIR().value_or(std::monostate {});
        if (auto s_ptr = std::get_if<string>(&lhs_vrt)) {
            lhs = tmp_name + "." + *s_ptr;
        }
        // "ExpressionList"
        // Create an instruction "IRMethodCall"
        const auto n_vrt = this->children.at(2)->generateIR().value_or(std::monostate {});
        if (auto szt_ptr = std::get_if<string>(&n_vrt)) {
            n = *szt_ptr;
        }
        tmp_name = cfg::Tac::generateTmpVarName();
        std::shared_ptr<cfg::Tac> instruction = std::make_shared<cfg::IRMethodCall>(lhs, n, tmp_name);
        cur_bb->addInstruction(instruction);

        return tmp_name;
    }
    // "Expression" -> "keyword:this", "Identifier"
    // "Expression" -> "keyword:this", "Identifier", "ExpressionList"
    else if (size <= 3 && type == "keyword") {
        string tmp_name, lhs, n;
        // "keyword:this"
        // turn "this" into instruction "IRAlloc"
        string class_name = Expression::st.getParentScope()->getScopeTitle();
        tmp_name = cfg::Tac::generateTmpVarName();
        cur_bb->addInstruction(std::make_shared<cfg::IRAlloc>(class_name, tmp_name));
        // "Identifier"
        const auto lhs_vrt = this->children.at(1)->generateIR().value_or(std::monostate {});
        if (auto s_ptr = std::get_if<string>(&lhs_vrt)) {
            lhs = tmp_name + "." + *s_ptr;
        }
        // "ExpressionList"
        // Create an instruction "IRMethodCall"
        const auto n_vrt = this->children.at(2)->generateIR().value_or(std::monostate {});
        if (auto szt_ptr = std::get_if<string>(&n_vrt)) {
            n = *szt_ptr;
        }
        tmp_name = cfg::Tac::generateTmpVarName();
        std::shared_ptr<cfg::Tac> instruction = std::make_shared<cfg::IRMethodCall>(lhs, n, tmp_name);
        cur_bb->addInstruction(instruction);

        return tmp_name;
    }
    return std::nullopt;
}
