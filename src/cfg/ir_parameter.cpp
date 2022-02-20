#include "ir_parameter.h"
using cfg::IRParameter;
using std::string;

IRParameter::IRParameter() : Tac() {}
IRParameter::IRParameter(string lhs) : Tac("param", std::move(lhs), "", "") {}
