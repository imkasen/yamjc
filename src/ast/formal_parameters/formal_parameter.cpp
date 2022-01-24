#include "ast/formal_parameters/formal_parameter.h"
using std::string;

FormalParameter::FormalParameter() : Node() {}
FormalParameter::FormalParameter(string t, string v) : Node(std::move(t), std::move(v)) {}
