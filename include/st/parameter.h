#ifndef ST_PARAMETER_H
#define ST_PARAMETER_H

#include "variable.h"

namespace st {

// formal parameters in "Method"
class Parameter : public Variable {
public:
    Parameter();
    Parameter(std::string name, std::string type);
    Parameter(std::string name, std::string type, std::string record);
    ~Parameter() override = default;
};

}  // namespace st

#endif
