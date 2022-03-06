#ifndef SMI_DATA_STK_H
#define SMI_DATA_STK_H

#include <optional>
#include <stack>
#include <string>
#include <variant>
#include <vector>

using DataTypes = std::variant<std::monostate, int, std::string, std::vector<int>>;

namespace smi {

class DataStk {
private:
    std::stack<DataTypes> stk;

public:
    DataStk() = default;
    ~DataStk() = default;

    void push(const DataTypes &dt);

    [[nodiscard]] std::size_t size() const;
    [[nodiscard]] std::optional<DataTypes> top() const;
    std::optional<DataTypes> pop();
};

}  // namespace smi

#endif
