#include "st_class.h"
using st::Method;
using st::STClass;
using std::string;

STClass::STClass(string name, string type) : Variable(std::move(name), std::move(type), "Class") {}

std::unordered_map<std::string, std::shared_ptr<Method>> STClass::getMethods() const {
    return this->methods;
}

void STClass::addMethod(const std::shared_ptr<Method> &method) {
    const auto &[itr, ret] = this->methods.emplace(method->getName(), method);
    if (!ret) {  // false
        std::cerr << "The method " << method->getName() << " already exists in the class!" << std::endl;
    }
}

/*
 * @return std::shared_ptr<Method> | std::nullopt
 */
std::optional<std::shared_ptr<Method>> STClass::lookupMethod(const string &name) const {
    // iterator: std::unordered_map<string, std::shared_ptr<Method>>::iterator
    auto iterator = this->methods.find(name);
    if (iterator != this->methods.end()) {  // exists
        return iterator->second;
    } else {
        return std::nullopt;
    }
}
