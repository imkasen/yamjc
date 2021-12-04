#ifndef METHOD_H
#define METHOD_H

#include <deque>
#include "parameter.h"

class Method : public Parameter {
private:
    std::deque<std::shared_ptr<Parameter>> parameters;

public:
    Method();
    Method(std::string name, std::string type);

    std::deque<std::shared_ptr<Parameter>> getParameters() const;
    void addParameter(const std::shared_ptr<Parameter> &parameter);
    std::optional<std::shared_ptr<Parameter>> lookupParameter(const std::string &name) const;
};

#endif