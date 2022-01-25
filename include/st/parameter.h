#ifndef PARAMETER_H
#define PARAMETER_H

#include "variable.h"

// formal parameters in "Method"
class Parameter : public Variable {
public:
    Parameter();
    Parameter(std::string name, std::string type);
    Parameter(std::string name, std::string type, std::string record);
    ~Parameter() override = default;
};

#endif
