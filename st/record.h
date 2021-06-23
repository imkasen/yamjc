#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <string>

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
    std::string id;
    std::string type;

public:
    Record();
    Record(std::string id, std::string type);

    void setId(const std::string &r_id);
    void setType(const std::string &r_type);
    const std::string getId() const;
    const std::string getType() const;
    const std::string getRecord() const;
    
    const void printRecord() const;

    virtual ~Record() = default;
};

#endif