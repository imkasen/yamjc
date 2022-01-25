#ifndef ST_CLASS_H
#define ST_CLASS_H

#include "method.h"

class STClass : public Variable {
private:
    std::unordered_map<std::string, std::shared_ptr<Method>> methods;

public:
    STClass();
    STClass(std::string name, std::string type);
    ~STClass() override = default;

    std::unordered_map<std::string, std::shared_ptr<Method>> getMethods() const;

    void addMethod(const std::shared_ptr<Method> &method);
    std::optional<std::shared_ptr<Method>> lookupMethod(const std::string &name) const;
};

#endif