#include "record.h"
using std::string;

Record::Record()
{
    this->id = "uninitialised";
    this->type = "uninitialised";
}

Record::Record(string id, string type) : id(id), type(type) {}

void Record::setId(const string &r_id)
{
    this->id = r_id;
}

void Record::setType(const string &r_type)
{
    this->type = r_type;
}

const string Record::getId() const
{
    return this->id;
}

const string Record::getType() const
{
    return this->type;
}

const string Record::getRecord() const
{
    return this->RECORD;
}

const void Record::printRecord() const
{
    std::cout << "name: " << this->getId() << "; record: " << this->getRecord() << "; type: " << this->getType() << std::endl;
}
