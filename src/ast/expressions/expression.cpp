#include "ast/expressions/expression.h"
using std::size_t;
using std::string;

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
 * @brief:
 *   2.    "Expression"
 *              |
 *      "PrimaryExpression"
 *
 *        "Expression"       or   "Expression"
 *           |                        |
 *      "AllocExpression"       "ArrayAllocExpression"
 *
 *   4. "Expression"   or  "Expression"    or   "Expression"
 *          |                   |                   |
 *        "int"             "boolean"          "keyword:this"
 *
 *   5.                   "Expression"
 *                 /           |          \
 *    "AllocExpression"  "Identifier"  "ExpressionList"
 *
 *                        "Expression"
 *            /              |         \
 *   "PrimaryExpression"  "Identifier"  ["ExpressionList"]
 *
 *   6.            "Expression"
 *          /             |        \
 *     "keyword:this"  "Identifier"  ["ExpressionList"]
 *
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

    // 2.
    // "Expression" -> "PrimaryExpression"
    if (this->children.size() == 1 && this->children.at(0)->getType() == "PrimaryExpression") {
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
    // "Expression" -> "AllocExpression"
    // "Expression" -> "ArrayAllocExpression"
    else if (this->children.size() == 1 && (this->children.at(0)->getType() == "AllocExpression" ||
                                            this->children.at(0)->getType() == "ArrayAllocExpression")) {
        return this->children.at(0)->checkSemantics();
    }
    // 4.
    // "Expression" -> "int"
    // "Expression" -> "boolean"
    // "Expression" -> "keyword:this"
    else if (this->children.size() == 1) {
        string type = this->children.at(0)->getType();
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
    // 5.
    // "Expression" -> "AllocExpression", "Identifier", "ExpressionList"
    else if (this->children.size() <= 3 && this->children.at(0)->getType() == "AllocExpression") {
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
    // "Expression" -> "PrimaryExpression", "Identifier"
    // "Expression" -> "PrimaryExpression", "Identifier", "ExpressionList"
    else if (this->children.size() <= 3 && this->children.at(0)->getType() == "PrimaryExpression") {
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
    else if (this->children.size() <= 3 && this->children.at(0)->getValue() == "this") {
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
 * @brief:
 *
 *   3. "Expression:!"
 *            |
 *      "Expression"
 *
 *   7.       "Expression"
 *             /       \
 *      "Expression"    ...
 *
 * @return: std::nullopt || string
 */
/*
std::optional<string> Expression::checkSemantics() {
    string class_name;
    string method_name;
    string var_name;
    std::shared_ptr<Record> c_record_ptr;
    std::shared_ptr<Record> v_record_ptr;
    std::shared_ptr<Record> m_record_ptr;
    std::shared_ptr<STClass> class_ptr;

    // 3.
    // "Expression:!" -> "Expression"
    else if (this->children.size() == 1 && this->getValue() == "!") {
        return this->children.at(0)->checkSemantics();
    }
    // 7.
    // "Expression" -> "Expression", ...
    else if (this->children.size() <= 3 && this->children.at(0)->getType() == "Expression") {
        // "Expression:!" -> "Expression", "Identifier"
        // "Expression:!" -> "Expression", "Identifier", "ExpressionList"
        if (this->getValue() == "!" && this->children.at(1)->getType() == "Identifier") {
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
                    string msg = "[Semantic Analysis] - Error: Method \"" + method_name +
                                 "\" does not exist in scope \"" + Expression::st.getScopeTitle() + "\"!";
                    Expression::printErrMsg(msg);
                }
            }

            this->checkParameters(m_record_ptr);

            return m_record_ptr->getType();
        }
    }

    return std::nullopt;
}
 */

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

// ---------
// TODO: UnaryExpression
