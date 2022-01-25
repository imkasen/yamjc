#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <memory>
#include <string>
#include <utility>

/*
 * The basic class in tree-based symbol table implementation.
 *
 * Variable : Record     // means local variables
 * Parameter : Variable  // means formal parameters
 * Method : Variable
 * STClass : Variable
 */
class Record {
protected:
    std::string name;
    std::string type;
    std::string record;

public:
    Record();
    Record(std::string name, std::string type, std::string record);
    virtual ~Record() = default;

    void setName(const std::string &r_name);
    void setRecord(const std::string &r_record);
    void setType(const std::string &r_type);

    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getRecord() const;
    [[nodiscard]] std::string getType() const;

    [[nodiscard]] std::string printRecord() const;
};

#endif