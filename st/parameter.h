#ifndef PARAMETER_H
#define PARAMETER_H

#include "variable.h"

class Parameter : public Variable
{
public:
    Parameter();
    Parameter(std::string name, std::string type);
};

#endif
