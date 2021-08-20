#ifndef METHOD_H
#define METHOD_H

#include "parameter.h"

class Method : public Parameter
{
private:
    std::unordered_map<std::string, std::shared_ptr<Parameter>> parameters;
    
public:
    Method();
    Method(std::string name, std::string type);

    std::unordered_map<std::string, std::shared_ptr<Parameter>> getParameters() const;

    void addParameter(const std::shared_ptr<Parameter> &parameter);
    std::optional<std::shared_ptr<Parameter>> lookupParameter(const std::string &name) const;

};


#endif