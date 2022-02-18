#ifndef ST_METHOD_H
#define ST_METHOD_H

#include <deque>
#include "parameter.h"

namespace st {

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

}  // namespace st

#endif