#ifndef ST_CLASS_H
#define ST_CLASS_H

#include "method.h"

class STClass : public Variable
{
private:
    inline static const std::string RECORD = "class";
    std::map<std::string, std::shared_ptr<Method>> methods;

public:
    STClass();
    STClass(std::string name, std::string type);

    void addMethod(const std::shared_ptr<Method> &method);
    std::optional<std::shared_ptr<Method>> lookupMethod(const std::string &name) const;

};

#endif