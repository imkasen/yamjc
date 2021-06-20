#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

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
    inline static const string RECORD = "record"; // requires c++17

protected:
    string id;
    string type;

public:
    Record();
    Record(string id, string type);

    void setId(string r_id);
    void setType(string r_type);
    const string getId() const;
    const string getType() const;
    const string getRecord() const;
    
    const void printRecord() const;
};

#endif