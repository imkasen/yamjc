#include "../../include/st/parameter.h"
using std::string;

Parameter::Parameter() : Variable() {}
Parameter::Parameter(string name, string type) : Variable(name, type, "Parameter") {}
Parameter::Parameter(string name, string type, string record) : Variable(name, type, record) {}
