#ifndef ST_CLASS_H
#define ST_CLASS_H

#include "method.h"

class STClass : public Variable
{
private:
    inline static const std::string RECORD = "class";
    std::map<std::string, Method> methods;

public:
    STClass();
    STClass(std::string id, std::string type);

    void addMethod(Method method);
    std::optional<Method> lookupMethod(std::string name) const;
};

#endif