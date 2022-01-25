#ifndef METHOD_H
#define METHOD_H

#include <deque>
#include "parameter.h"

class Method : public Parameter {
private:
    // use "deque" to keep formal parameters in order
    std::deque<std::shared_ptr<Parameter>> parameters;

public:
    Method();
    Method(std::string name, std::string type);
    ~Method() override = default;

    std::deque<std::shared_ptr<Parameter>> getParameters() const;
    void addParameter(const std::shared_ptr<Parameter> &parameter);
    std::optional<std::shared_ptr<Parameter>> lookupParameter(const std::string &name) const;
};

#endif