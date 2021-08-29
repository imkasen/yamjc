#include "ast/return.h"
using std::string;
using std::cerr;
using std::endl;
using std::exit;

Return::Return() : Node() {}
Return::Return(string t, string v) : Node(std::move(t), std::move(v)) {}

std::optional<string> Return::checkSemantics()
{
    string return_type = this->children.at(0)->checkSemantics().value_or("");
    string method_name = Return::st.getScopeTitle();
    auto record_ptr = Return::st.lookupRecord(method_name).value_or(nullptr);
    if (record_ptr)
    {
        string record_ptr_type = record_ptr->getType();
        if (record_ptr_type != return_type)
        {
            cerr << "[Semantic Analysis] - Error: return type \"" << return_type
                << "\" does not match the declaration (\"" << record_ptr_type << "\")!" << endl;
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        cerr << "[Semantic Analysis] - Error: Can not find \"" << method_name << "\"!" << endl;
        exit(EXIT_FAILURE);
    }

    return std::nullopt;
}
