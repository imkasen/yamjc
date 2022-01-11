#include "ast/statement.h"
using std::cerr;
using std::endl;
using std::exit;
using std::string;

Statement::Statement() : Node() {}
Statement::Statement(string t, string v) : Node(std::move(t), std::move(v)) {}

/*
 * @brief:
 *   1. Node: "Statement: ="
 *        Compare types of lhs and rhs.
 *   2. Node: "Statement: S.O.PRINTLN"
 *        Traverse child nodes, and check the return value.
 *        The grammar restricts that only integers can be print,
 *        so the return value must be "int".
 *   3. Node: "Statement: IF" || "Statement: WHILE"
 * @return: std::nullopt
 */
std::optional<string> Statement::checkSemantics() {
    // 1.
    if (this->getValue() == "=") {
        // e.g. xxx = 123;
        //      xxx = NEW ...;
        // etc...
        if (this->children.size() == 2) {
            string lhs_name = this->children.at(0)->checkSemantics().value_or("");  // "Identifier"
            string rhs_type = this->children.at(1)->checkSemantics().value_or("");  // "Expression"

            auto record_ptr = Statement::st.lookupRecord(lhs_name).value_or(nullptr);
            if (record_ptr) {
                string lhs_record_type = record_ptr->getType();

                // lhs and rhs are different types,
                // or "Class" extends from "Class".
                if (lhs_record_type != rhs_type && rhs_type.find(lhs_record_type) == string::npos) {
                    cerr << "[Semantic Analysis] - Error: Can not assign \"" << rhs_type << "\" (rhs) to \""
                         << lhs_record_type << "\" (lhs) in the scope \"" << Statement::st.getScopeTitle() << "\"!"
                         << endl;
                    exit(EXIT_FAILURE);
                }
            } else {
                cerr << "[Semantic Analysis] - Error: Variable \"" << lhs_name << "\" does not exist in scope \""
                     << Statement::st.getScopeTitle() << "\"!" << endl;
                exit(EXIT_FAILURE);
            }
        }
        // e.g. number[0] = 20;
        else if (this->children.size() == 3) {
            string lhs_name = this->children.at(0)->checkSemantics().value_or("");  // "Identifier"
            string pos_type = this->children.at(1)->checkSemantics().value_or("");
            string rhs_type = this->children.at(2)->checkSemantics().value_or("");

            auto record_ptr = Statement::st.lookupRecord(lhs_name).value_or(nullptr);
            if (record_ptr) {
                if (pos_type != "int") {
                    cerr << R"([Semantic Analysis] - Error: only "int" can be used to access array's position in scope ")"
                         << Statement::st.getScopeTitle() << "\"!" << endl;
                    exit(EXIT_FAILURE);
                }
                string lhs_record_type = record_ptr->getType();
                if (lhs_record_type != "int[]" || rhs_type != "int") {
                    cerr << "[Semantic Analysis] - Error: Can not assign \"" << rhs_type << "\" (rhs) to \""
                         << lhs_record_type << "\" (lhs) in the scope \"" << Statement::st.getScopeTitle() << "\"!"
                         << endl;
                    exit(EXIT_FAILURE);
                }
            } else {
                cerr << "[Semantic Analysis] - Error: Variable \"" << lhs_name << "\" does not exist in scope \""
                     << Statement::st.getScopeTitle() << "\"!" << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
    // 2.
    else if (this->getValue() == "S.O.PRINTLN") {
        /*
         * Expectation:
         *   the returned string is "int", do nothing.
         * Non-expectation:
         *   the returned string is not "int", print the error message.
         */
        string type = this->children.at(0)->checkSemantics().value_or("");

        if (type != "int") {
            cerr << R"([Semantic Analysis] - Error: only "int" can be print in scope ")"
                 << Statement::st.getScopeTitle() << "\"!" << endl;
            exit(EXIT_FAILURE);
        }
    }
    // 3.
    else if (this->getValue() == "IF" || this->getValue() == "WHILE") {
        string type = this->children.at(0)->checkSemantics().value_or("");
        if (type != "boolean") {
            cerr << R"([Semantic Analysis] - Error: IF WHILE condition should be "boolean" in scope ")"
                 << Statement::st.getScopeTitle() << "\"!" << endl;
            exit(EXIT_FAILURE);
        }

        for (std::size_t i = 1; i < this->children.size(); ++i) {
            this->children.at(i)->checkSemantics();
        }
    }

    return std::nullopt;
}
