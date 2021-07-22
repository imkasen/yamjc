#ifndef METHOD_H
#define METHOD_H

#include "variable.h"

class Method : public Variable
{
private:
    inline static const std::string RECORD = "method";
    std::map<std::string, std::shared_ptr<Variable>> parameters;
    
public:
    Method();
    Method(std::string name, std::string type);

    void addParameter(const std::shared_ptr<Variable> &parameter);
    std::optional<std::shared_ptr<Variable>> lookupParameter(const std::string &name) const;

};


#endif