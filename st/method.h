#ifndef METHOD_H
#define METHOD_H

#include "variable.h"

class Method : public Variable
{
private:
    inline static const string RECORD = "method";
    std::map<string, Variable> parameters;
    
public:
    Method();
    Method(string id, string type);

    void addParameter(Variable parameter);
    optional<Variable> lookupParameter(string name) const;
};


#endif