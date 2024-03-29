#ifndef ST_CLASS_H
#define ST_CLASS_H

#include "method.h"

namespace st {

class STClass : public Variable {
private:
    std::unordered_map<std::string, std::shared_ptr<Method>> methods;

public:
    STClass() = delete;
    STClass(std::string name, std::string type);
    ~STClass() override = default;

    std::unordered_map<std::string, std::shared_ptr<Method>> getMethods() const;

    void addMethod(const std::shared_ptr<Method> &method);
    std::optional<std::shared_ptr<Method>> lookupMethod(const std::string &name) const;
};

}  // namespace st

#endif