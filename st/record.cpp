#include "record.h"

Record::Record()
{
    id = "uninitialised";
    type = "uninitialised";
}

Record::Record(string id, string type) : id(id), type(type) {}

void Record::setId(string id) 
{
    this->id = id;
}

void Record::setType(string type)
{
    this->type = type;
}

void Record::printRecord()
{
    cout << "name: " << this->id << "; record: " << this->record << "; type: " << this->type << endl;
}
