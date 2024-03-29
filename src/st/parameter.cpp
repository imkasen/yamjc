#include "parameter.h"
using st::Parameter;
using std::string;

Parameter::Parameter(string name, string type)
    : Variable(std::move(name), std::move(type), "Parameter") {}
Parameter::Parameter(string name, string type, string record)
    : Variable(std::move(name), std::move(type), std::move(record)) {}
