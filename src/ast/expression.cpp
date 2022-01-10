#include "ast/expression.h"
using std::cerr;
using std::endl;
using std::exit;
using std::size_t;
using std::string;

Expression::Expression() : Node() {}
Expression::Expression(string t, string v) : Node(std::move(t), std::move(v)) {}

/*
 * @brief:
 *   1. "ExpressionList"
 *
 *   2.    "Expression"
 *              |
 *      "PrimaryExpression"
 *
 *   3. "Expression:!"
 *            |
 *      "Expression"
 *
 *   4. "Expression"   or  "Expression"    or   "Expression"
 *          |                   |                   |
 *        "int"             "boolean"             "this"
 *
 *   5.                   "Expression"                or                       "Expression"
 *                       /           \                                     /        |        \
 *      "PrimaryExpression"           "Identifier"         "PrimaryExpression"  "Identifier"  "ExpressionList"
 *
 *   6.  "Expression"             or                 "Expression"
 *         /     \                                /       |        \
 *      "this"  "Identifier"                  "this"  "Identifier"  "ExpressionList"
 *
 *   7.       "Expression"
 *             /       \
 *      "Expression"    ...
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

    // 1.
    // "ExpressionList"
    if (this->getType() == "ExpressionList") {
        string parameter_type_list;

        // Splice formal parameter types, "xxx xxx ..."
        for (auto child : this->children) {
            parameter_type_list += child->checkSemantics().value_or("") + " ";
        }

        return parameter_type_list;
    }
    // 2.
    // "Expression" -> "PrimaryExpression"
    else if (this->children.size() == 1 && this->children.at(0)->getType() == "PrimaryExpression") {
        // "PrimaryExpression:NEW"
        if (this->children.at(0)->getValue() == "NEW") {
            class_name = this->children.at(0)->checkSemantics().value_or("");
            c_record_ptr = Expression::st.lookupRecordInRoot(class_name).value_or(nullptr);
            if (!c_record_ptr) {
                cerr << "[Semantic Analysis] - Error: Class \"" << class_name << "\" does not exist!" << endl;
                exit(EXIT_FAILURE);
            }

            return c_record_ptr->getType();
        }
        // "PrimaryExpression:New int[]"
        else if (this->children.at(0)->getValue() == "NEW int[]") {
            string type = this->children.at(0)->checkSemantics().value_or("");
            if (type != "int") {
                cerr << R"([Semantic Analysis] - Error: only "int" can be used to create "NEW int[]" in scope ")"
                     << Expression::st.getScopeTitle() << "\"!" << endl;
                exit(EXIT_FAILURE);
            }

            return "int[]";
        }
        // "PrimaryExpression"
        else if (this->children.at(0)->getValue().empty()) {
            // Check parameters
            var_name = this->children.at(0)->checkSemantics().value_or("");
            if (var_name == "int" || var_name == "boolean") {
                return var_name;
            }
            v_record_ptr = Expression::st.lookupRecord(var_name).value_or(nullptr);
            if (v_record_ptr) {
                return v_record_ptr->getType();
            } else {
                cerr << "[Semantic Analysis] - Error: Variable \"" << var_name << "\" does not exist in scope \""
                     << Expression::st.getScopeTitle() << "\"!" << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
    // 3.
    // "Expression:!" -> "Expression"
    else if (this->children.size() == 1 && this->getValue() == "!") {
        return this->children.at(0)->checkSemantics();
    }
    // 4.
    // "Expression" -> "int"
    // "Expression" -> "boolean"
    // "Expression" -> "this"
    else if (this->children.size() == 1) {
        string type = this->children.at(0)->getType();
        if (type == "this") {
            v_record_ptr = Expression::st.lookupRecord(type).value_or(nullptr);
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
    // "Expression" -> "PrimaryExpression", "Identifier"
    // "Expression" -> "PrimaryExpression", "Identifier", "ExpressionList"
    else if (this->children.size() <= 3 && this->children.at(0)->getType() == "PrimaryExpression") {
        // "PrimaryExpression:NEW"
        if (this->children.at(0)->getValue() == "NEW") {
            class_name = this->children.at(0)->checkSemantics().value_or("");
            method_name = this->children.at(1)->checkSemantics().value_or("");

            c_record_ptr = Expression::st.lookupRecordInRoot(class_name).value_or(nullptr);
            class_ptr = std::dynamic_pointer_cast<STClass>(c_record_ptr);

            if (!class_ptr) {
                cerr << "[Semantic Analysis] - Error: Class \"" << class_name << "\" does not exist!" << endl;
                exit(EXIT_FAILURE);
            } else {
                m_record_ptr = class_ptr->lookupMethod(method_name).value_or(nullptr);
                if (!m_record_ptr) {
                    cerr << "[Semantic Analysis] - Error: Method \"" << method_name << "\" does not exist in scope \""
                         << Expression::st.getScopeTitle() << "\"!" << endl;
                    exit(EXIT_FAILURE);
                }
            }

            if (!this->checkParameters(m_record_ptr)) {
                exit(EXIT_FAILURE);
            }

            return m_record_ptr->getType();
        }
        // "PrimaryExpression"
        else {
            var_name = this->children.at(0)->checkSemantics().value_or("");
            method_name = this->children.at(1)->checkSemantics().value_or("");

            v_record_ptr = Expression::st.lookupRecord(var_name).value_or(nullptr);
            if (!v_record_ptr) {
                cerr << "[Semantic Analysis] - Error: Variable \"" << var_name << "\" does not exist in scope \""
                     << Expression::st.getScopeTitle() << "\"!" << endl;
                exit(EXIT_FAILURE);
            }

            class_name = v_record_ptr->getType();
            c_record_ptr = Expression::st.lookupRecordInRoot(class_name).value_or(nullptr);
            class_ptr = std::dynamic_pointer_cast<STClass>(c_record_ptr);

            if (!class_ptr) {
                cerr << "[Semantic Analysis] - Error: Class \"" << class_name << "\" does not exist!" << endl;
                exit(EXIT_FAILURE);
            } else {
                m_record_ptr = class_ptr->lookupMethod(method_name).value_or(nullptr);
                if (!m_record_ptr) {
                    cerr << "[Semantic Analysis] - Error: Method \"" << method_name << "\" does not exist in scope \""
                         << Expression::st.getScopeTitle() << "\"!" << endl;
                    exit(EXIT_FAILURE);
                }
            }

            if (!this->checkParameters(m_record_ptr)) {
                exit(EXIT_FAILURE);
            }

            return m_record_ptr->getType();
        }
    }
    // 6.
    // "Expression" -> "this", "Identifier"
    // "Expression" -> "this", "Identifier", "ExpressionList"
    else if (this->children.size() <= 3 && this->children.at(0)->getType() == "this") {
        method_name = this->children.at(1)->checkSemantics().value_or("");
        m_record_ptr = Expression::st.lookupRecord(method_name).value_or(nullptr);
        if (!m_record_ptr) {
            cerr << "[Semantic Analysis] - Error: Method \"" << method_name << "\" does not exist in scope \""
                 << Expression::st.getScopeTitle() << "\"!" << endl;
            exit(EXIT_FAILURE);
        }

        if (!this->checkParameters(m_record_ptr)) {
            exit(EXIT_FAILURE);
        }

        return m_record_ptr->getType();
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
                cerr << "[Semantic Analysis] - Error: Variable \"" << var_name << "\" does not exist in scope \""
                     << Expression::st.getScopeTitle() << "\"!" << endl;
                exit(EXIT_FAILURE);
            }

            class_name = v_record_ptr->getType();
            c_record_ptr = Expression::st.lookupRecordInRoot(class_name).value_or(nullptr);
            class_ptr = std::dynamic_pointer_cast<STClass>(c_record_ptr);

            if (!class_ptr) {
                cerr << "[Semantic Analysis] - Error: Class \"" << class_name << "\" does not exist!" << endl;
                exit(EXIT_FAILURE);
            } else {
                m_record_ptr = class_ptr->lookupMethod(method_name).value_or(nullptr);
                if (!m_record_ptr) {
                    cerr << "[Semantic Analysis] - Error: Method \"" << method_name << "\" does not exist in scope \""
                         << Expression::st.getScopeTitle() << "\"!" << endl;
                    exit(EXIT_FAILURE);
                }
            }

            if (!this->checkParameters(m_record_ptr)) {
                exit(EXIT_FAILURE);
            }

            return m_record_ptr->getType();
        }
        // "Expression" -> "Expression", "Expression"
        else if (this->children.size() == 2 && this->getValue() != "[]" &&
                 this->getValue() != ".") {  // Skip "Expression:[]", "Expression:."
            string lhs = this->children.at(0)->checkSemantics().value_or("");
            string rhs = this->children.at(1)->checkSemantics().value_or("");
            if (!lhs.empty() && !rhs.empty() && lhs == rhs) {
                // "IF", "WHILE"
                if (this->getValue() == ">" || this->getValue() == "<") {
                    return "boolean";
                }
                return lhs;
            } else {
                cerr << "[Semantic Analysis] - Error: lhs (\"" << lhs << "\") and rhs (\"" << rhs
                     << "\") variable types are different in scope \"" << Expression::st.getScopeTitle() << "\"!"
                     << endl;
                exit(EXIT_FAILURE);
            }
        }
        // "Expression:." -> "Expression", "Length"
        else if (this->children.size() == 2 && this->getValue() == ".") {
            string lhs = this->children.at(0)->checkSemantics().value_or("");
            string rhs;
            if (this->children.at(1)->getType() == "Length") {
                rhs = "int";
                if (!lhs.empty() && !rhs.empty() && lhs == "int[]") {
                    return rhs;
                } else {
                    cerr << R"([Semantic Analysis] - Error: ".length" can only be applied to "int[]" in scope ")"
                         << Expression::st.getScopeTitle() << "\"!" << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    return std::nullopt;
}

/*
 * @brief: Check whether formal parameters meet the syntax requirements, e.g. order, number...
 * @return: Boolean
 */
bool Expression::checkParameters(const std::shared_ptr<Record> &m_record_ptr) {
    std::shared_ptr<Method> method_ptr;
    std::deque<string> p_deque;

    if (this->children.size() == 3) {
        method_ptr = std::dynamic_pointer_cast<Method>(m_record_ptr);

        string parameter_type_list = this->children.at(2)->checkSemantics().value_or("");
        // Split string
        Expression::strSplit(p_deque, parameter_type_list, " ");

        // check number
        if (p_deque.size() != method_ptr->getParameters().size()) {
            cerr << "[Semantic Analysis] - Error: Parameter numbers do not match in scope \""
                 << Expression::st.getScopeTitle() << "\"!" << endl;
            return false;
        }

        // check order
        for (size_t i = 0; i < method_ptr->getParameters().size(); ++i) {
            string type_from_m = method_ptr->getParameters().at(i)->getType();
            string type_from_p = p_deque.at(i);

            if (type_from_p != type_from_m) {
                // "Class" extends "Class" situation
                // e.g. Visitor = Visitor Parent_Visitor
                // warning: not a rigorous judgment...
                auto c_record_ptr = Expression::st.lookupRecordInRoot(type_from_p).value_or(nullptr);
                string c_record_ptr_type = c_record_ptr->getType();
                if (c_record_ptr_type.find(type_from_m) != string::npos) {
                    return true;
                }

                cerr << "[Semantic Analysis] - Error: Parameter types (\"" << type_from_m << "\" - \"" << type_from_p
                     << "\") do not match in scope \"" << Expression::st.getScopeTitle() << "\"!" << endl;
                return false;
            }
        }
    }

    return true;
}

void Expression::strSplit(std::deque<std::string> &deque, const std::string &text, const std::string &delimiter) {
    size_t pos;
    string text_str = text;

    // Not end with the delimiter
    if (text_str.rfind(delimiter) != (text_str.length() - delimiter.length())) {
        text_str += delimiter;
    }

    while ((pos = text_str.find(delimiter)) != string::npos) {
        deque.push_back(text_str.substr(0, pos));
        text_str.erase(0, pos + delimiter.length());
    }
}

// ---------
// TODO: Refactor
// TODO: reduce IF nesting
// TODO: reduce ERROR message
