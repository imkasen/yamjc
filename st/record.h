#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

class Record
{
private:
    string record = "record";

protected:
    string id;
    string type;

public:
    Record();
    Record(string id, string type);

    void setId(string id);
    void setType(string type);
    void printRecord();
};

#endif