#include "ast/expression.h"
using std::string;
using std::size_t;

Expression::Expression() : Node() {}
Expression::Expression(string t, string v) : Node(std::move(t), std::move(v)) {}

std::optional<string> Expression::checkSemantics()
{
    string class_name;
    string method_name;
    string var_name;
    std::shared_ptr<Record> c_record_ptr;
    std::shared_ptr<Record> v_record_ptr;
    std::shared_ptr<Record> m_record_ptr;

    // ExpressionList
    if (this->getType() == "ExpressionList")
    {
        // check parameters
        string parameter_type_list;

        for (auto &child : this->children)
        {
            parameter_type_list += child->checkSemantics().value_or("") + " ";
        }

        return parameter_type_list;
    }
    // Expression -> PrimaryExpression
    else if (this->children.size() == 1 && this->children.at(0)->getType() == "PrimaryExpression")
    {
        // PrimaryExpression:NEW
        if (this->children.at(0)->getValue() == "NEW")
        {
            class_name = this->children.at(0)->checkSemantics().value_or("");
            c_record_ptr = Expression::st.lookupRecordInRoot(class_name).value_or(nullptr);
            if (!c_record_ptr)
            {
                std::cerr << "[Semantic Analysis] - Error: Class \"" << class_name
                    << "\" does not exist!" << std::endl;
                return std::nullopt;
            }
        }
        // PrimaryExpression
        else if (this->children.at(0)->getValue().empty())
        {
            // check parameters
            var_name = this->children.at(0)->checkSemantics().value_or("");
            v_record_ptr = Expression::st.lookupRecord(var_name).value_or(nullptr);
            if (v_record_ptr)
            {
                return v_record_ptr->getType();
            }
            else
            {
                std::cerr << "[Semantic Analysis] - Error: Variable \"" << var_name
                    << "\" does not exist!" << std::endl;
                return std::nullopt;
            }
        }
    }
    // Expression -> Number, Boolean, ...
    else if (this->children.size() == 1)
    {
        // check parameters
        return this->children.at(0)->getType();
    }
    // Expression -> PrimaryExpression, Identifier
    // Expression -> PrimaryExpression, Identifier, ExpressionList
    else if (this->children.size() <= 3 && this->children.at(0)->getType() == "PrimaryExpression")
    {
        // PrimaryExpression:NEW
        if (this->children.at(0)->getValue() == "NEW")
        {
            class_name = this->children.at(0)->checkSemantics().value_or("");
            method_name = this->children.at(1)->checkSemantics().value_or("");

            c_record_ptr = Expression::st.lookupRecordInRoot(class_name).value_or(nullptr);
            auto class_ptr = std::dynamic_pointer_cast<STClass>(c_record_ptr);

            if (!class_ptr)
            {
                std::cerr << "[Semantic Analysis] - Error: Class \"" << class_name
                    << "\" does not exist!" << std::endl;
                return std::nullopt;
            }
            else
            {
                m_record_ptr = class_ptr->lookupMethod(method_name).value_or(nullptr);
                if (!m_record_ptr)
                {
                    std::cerr << "[Semantic Analysis] - Error: Method \"" << method_name
                        << "\" does not exist!" << std::endl;
                    return std::nullopt;
                }
            }

            if (!this->checkParameters(m_record_ptr))
            {
                return std::nullopt;
            }
        }
        // PrimaryExpression
        else if (this->children.at(0)->getValue().empty())
        {
            var_name = this->children.at(0)->checkSemantics().value_or("");
            method_name = this->children.at(1)->checkSemantics().value_or("");

            v_record_ptr = Expression::st.lookupRecord(var_name).value_or(nullptr);
            if (!v_record_ptr)
            {
                std::cerr << "[Semantic Analysis] - Error: Variable \"" << var_name
                    << "\" does not exist!" << std::endl;
                return std::nullopt;
            }

            class_name = v_record_ptr->getType();
            c_record_ptr = Expression::st.lookupRecordInRoot(class_name).value_or(nullptr);
            auto class_ptr = std::dynamic_pointer_cast<STClass>(c_record_ptr);

            if (!class_ptr)
            {
                std::cerr << "[Semantic Analysis] - Error: Class \"" << class_name
                    << "\" does not exist!" << std::endl;
                return std::nullopt;
            }
            else
            {
                m_record_ptr = class_ptr->lookupMethod(method_name).value_or(nullptr);
                if (!m_record_ptr)
                {
                    std::cerr << "[Semantic Analysis] - Error: Method \"" << method_name
                        << "\" does not exist!" << std::endl;
                    return std::nullopt;
                }
            }

            if (!this->checkParameters(m_record_ptr))
            {
                return std::nullopt;
            }

            // if: Expression -> PrimaryExpression -> Expression ...
            return m_record_ptr->getType();
        }
    }

    return std::nullopt;
}

bool Expression::checkParameters(const std::shared_ptr<Record> &m_record_ptr)
{
    std::shared_ptr<Method> method_ptr;
    std::deque<string> p_deque;

    if (this->children.size() == 3)
    {
        if (m_record_ptr)
        {
            method_ptr = std::dynamic_pointer_cast<Method>(m_record_ptr);
        }

        string parameter_type_list = this->children.at(2)->checkSemantics().value_or("");
        // split string
        Expression::strSplit(p_deque, parameter_type_list, " ");

        if (p_deque.size() != method_ptr->getParameters().size())
        {
            std::cerr << "[Semantic Analysis] - Error: Parameter numbers do not match!" << std::endl;
            return false;
        }

        for (size_t i = 0; i < method_ptr->getParameters().size(); ++i)
        {
            string type_from_m = method_ptr->getParameters().at(i)->getType();
            string type_from_p = p_deque.at(i);

            if (type_from_p != type_from_m)
            {
                // extends
                auto c_record_ptr = Expression::st.lookupRecordInRoot(type_from_p).value_or(nullptr);
                auto class_ptr = std::dynamic_pointer_cast<STClass>(c_record_ptr);
                if (class_ptr)
                {
                    std::deque<string> c_deque;
                    Expression::strSplit(c_deque, class_ptr->getType(), " ");

                    if (std::find(c_deque.begin(), c_deque.end(), type_from_m) != c_deque.end())
                    {
                        return true;
                    }
                }

                std::cerr << "[Semantic Analysis] - Error: Parameter types (\""
                << type_from_m << "\" - \"" << type_from_p
                << "\") do not match!" << std::endl;

                return false;
            }
        }
    }

    return true;
}

void Expression::strSplit(std::deque<std::string> &deque, const std::string &text, const std::string &delimiter)
{
    size_t pos;
    string text_str = text;

    // not end with delimiter
    if (text_str.rfind(delimiter) != (text_str.length() - delimiter.length()))
    {
        text_str += delimiter;
    }

    while ((pos = text_str.find(delimiter)) != string::npos)
    {
        deque.push_back(text_str.substr(0, pos));
        text_str.erase(0, pos + delimiter.length());
    }
}
