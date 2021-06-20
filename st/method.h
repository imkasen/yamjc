#ifndef METHOD_H
#define METHOD_H

#include "variable.h"

class Method : public Variable
{
private:
    inline static const std::string RECORD = "method";
    std::map<std::string, Variable> parameters;
    
public:
    Method();
    Method(std::string id, std::string type);

    void addParameter(Variable parameter);
    std::optional<Variable> lookupParameter(std::string name) const;
};


#endif