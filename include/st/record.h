#ifndef ST_RECORD_H
#define ST_RECORD_H

#include <iostream>
#include <memory>
#include <string>
#include <utility>

namespace st {

/*
 * The basic class in tree-based symbol table implementation.
 *
 * Variable : Record     // means local variables
 * Parameter : Variable  // means formal parameters
 * Method : Variable
 * STClass : Variable
 */
class Record {
private:
    std::string name;
    std::string type;
    std::string record;
public:
    Record() = delete;
    Record(std::string name, std::string type, std::string record);
    virtual ~Record() = default;

    [[maybe_unused]] void setName(std::string _name);
    [[maybe_unused]] void setRecord(std::string _record);
    void setType(std::string _type);

    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getRecord() const;
    [[nodiscard]] std::string getType() const;

    [[nodiscard]] std::string printRecord() const;
};

}  // namespace st

#endif