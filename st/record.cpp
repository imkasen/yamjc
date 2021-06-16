#include "record.h"

Record::Record()
{
    this->id = "uninitialised";
    this->type = "uninitialised";
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

string Record::getId() const
{
    return this->id;
}

string Record::getType() const
{
    return this->type;
}

string Record::getRecord() const
{
    return this->record;
}

void Record::printRecord() const
{
    cout << "name: " << this->getId() << "; record: " << this->getRecord() << "; type: " << this->getType() << endl;
}
