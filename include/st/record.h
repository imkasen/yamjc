#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <string>
#include <memory>

/*
 * The basic class in tree-based symbol table implementation.
 *
 * Variable : record
 * Parameter : Variable // parameter is variable
 * Method : Variable
 * STClass : Variable
 */
class Record
{
protected:
    std::string name;
    std::string type;
    std::string record;

public:
    Record();
    Record(std::string name, std::string type, std::string record);

    void setName(const std::string &r_name);
    void setRecord(const std::string &r_record);
    void setType(const std::string &r_type);
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getRecord() const;
    [[nodiscard]] std::string getType() const;
    
    [[nodiscard]] std::string printRecord() const;

    virtual ~Record() = default;
};

#endif