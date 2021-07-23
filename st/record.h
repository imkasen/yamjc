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
private:
    inline static const std::string RECORD = "record"; // requires c++17

protected:
    std::string name;
    std::string type;

public:
    Record();
    Record(std::string name, std::string type);

    void setName(const std::string &r_name);
    void setType(const std::string &r_type);
    const std::string getName() const;
    const std::string getType() const;
    const std::string getRecord() const;
    
    const void printRecord() const;

    virtual ~Record() = default;
};

#endif