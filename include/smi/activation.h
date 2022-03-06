#ifndef SMI_ACTIVATION_H
#define SMI_ACTIVATION_H

#include <istream>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

using DataTypes = std::variant<std::monostate, int, std::string, std::vector<int>>;

namespace smi {

class Activation {
private:
    std::unordered_map<std::string, DataTypes> local_variables;
    std::istream::pos_type pc;  // program counter, store the current instruction's position in the file

public:
    Activation() = default;
    explicit Activation(const std::istream::pos_type &npc);
    ~Activation() = default;

    void addLocalVar(const std::string &str, const DataTypes &dt);
    std::optional<DataTypes> getLocalVar(const std::string &str);

    void setPC(const std::istream::pos_type &npc);
    std::istream::pos_type getPC() const;
};

}  // namespace smi

#endif
