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

string Record::getId()
{
    return this->id;
}

string Record::getType()
{
    return this->type;
}

string Record::getRecord()
{
    return this->record;
}

void Record::printRecord()
{
    cout << "name: " << this->getId() << "; record: " << this->getRecord() << "; type: " << this->getType() << endl;
}
