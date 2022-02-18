#include "ast/formal_parameters/formal_parameter_list.h"
using ast::FormalParameterList;
using std::size_t;
using std::string;

FormalParameterList::FormalParameterList() : Node() {}
FormalParameterList::FormalParameterList(string t, string v) : Node(std::move(t), std::move(v)) {}
