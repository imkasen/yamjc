#include "ast/expression.h"
using std::string;

Expression::Expression() : Node() {}
Expression::Expression(string t, string v) : Node(std::move(t), std::move(v)) {}

std::optional<string> Expression::checkSemantics()
{
    // Expression -> PrimaryExpression
    if (this->children.size() == 1 && this->children.at(0)->getType() == "PrimaryExpression")
    {
        // PrimaryExpression:NEW
        if (this->children.at(0)->getValue() == "NEW")
        {
            string class_name = this->children.at(0)->checkSemantics().value_or("");
            std::shared_ptr<Record> c_record_ptr = Expression::st.lookupRecordInRoot(class_name).value_or(nullptr);
            if (!c_record_ptr)
            {
                std::cerr << "[Semantic Analysis] - Error: Class \"" << class_name << "\" does not exist!" << std::endl;
            }
        }
        // PrimaryExpression
        // else {}
    }
    // Expression -> PrimaryExpression, Identifier
    // Expression -> PrimaryExpression, Identifier, ExpressionList
    else if (this->children.size() <= 3 && this->children.at(0)->getType() == "PrimaryExpression")
    {
        // PrimaryExpression:NEW
        if (this->children.at(0)->getValue() == "NEW")
        {
            string class_name = this->children.at(0)->checkSemantics().value_or("");
            string method_name = this->children.at(1)->checkSemantics().value_or("");

            std::shared_ptr<Record> c_record_ptr = Expression::st.lookupRecordInRoot(class_name).value_or(nullptr);
            auto class_ptr = std::dynamic_pointer_cast<STClass>(c_record_ptr);
            std::shared_ptr<Record> m_record_ptr;

            if (!class_ptr)
            {
                std::cerr << "[Semantic Analysis] - Error: Class \"" << class_name << "\" does not exist!" << std::endl;
            }
            else
            {
                m_record_ptr = class_ptr->lookupMethod(method_name).value_or(nullptr);
                if (!m_record_ptr)
                {
                    std::cerr << "[Semantic Analysis] - Error: Method \"" << method_name << "\" does not exist!" << std::endl;
                }
            }
        }
        // PrimaryExpression
        else if (this->children.at(0)->getValue().empty())
        {
            string var_name = this->children.at(0)->checkSemantics().value_or("");
            string method_name = this->children.at(1)->checkSemantics().value_or("");

            auto v_record_ptr = Expression::st.lookupRecord(var_name).value_or(nullptr);
            if (!v_record_ptr)
            {
                std::cerr << "[Semantic Analysis] - Error: Variable \"" << var_name << "\" does not exist!" << std::endl;
            }

            string class_name = v_record_ptr->getType();
            auto c_record_ptr = Expression::st.lookupRecordInRoot(class_name).value_or(nullptr);
            auto class_ptr = std::dynamic_pointer_cast<STClass>(c_record_ptr);
            std::shared_ptr<Record> m_record_ptr;

            if (!class_ptr)
            {
                std::cerr << "[Semantic Analysis] - Error: Class \"" << class_name << "\" does not exist!" << std::endl;
            }
            else
            {
                m_record_ptr = class_ptr->lookupMethod(method_name).value_or(nullptr);
                if (!m_record_ptr)
                {
                    std::cerr << "[Semantic Analysis] - Error: Method \"" << method_name << "\" does not exist!" << std::endl;
                }
            }

            // if: Expression -> PrimaryExpression -> Expression ...
            return method_name;
        }
    }

    return std::nullopt;
}
