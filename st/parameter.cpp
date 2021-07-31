#include "parameter.h"

Parameter::Parameter() : Variable() {}
Parameter::Parameter(std::string name, std::string type) : Variable(name, type, "Parameter") {}
