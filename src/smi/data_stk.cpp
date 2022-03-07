#include "data_stk.h"
using smi::DataStk;

void DataStk::push(const DataTypes &dt) {
    this->stk.push(dt);
}

std::size_t DataStk::size() const {
    return this->stk.size();
}

std::optional<DataTypes> DataStk::top() const {
    if (!this->stk.empty()) {
        return this->stk.top();
    }
    return std::nullopt;
}

void DataStk::pop() {
    if (!this->stk.empty()) {
        this->stk.pop();
    }
}
