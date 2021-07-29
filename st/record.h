#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <string>
#include <memory>

/*
 * The basic class in tree-based symbol table implementation.
 *
 * Variable : Node
 * Method : Node
 * STClass : Node
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
    const std::string getName() const;
    const std::string getRecord() const;
    const std::string getType() const;
    
    const std::string printRecord() const;

    virtual ~Record() = default;
};

#endif