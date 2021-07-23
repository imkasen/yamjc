#include "record.h"
using std::string;

Record::Record()
{
    this->name = "uninitialised";
    this->type = "uninitialised";
}

Record::Record(string name, string type) : name(name), type(type) {}

void Record::setName(const std::string &r_name)
{
    this->name = r_name;
}

void Record::setType(const string &r_type)
{
    this->type = r_type;
}

const string Record::getName() const
{
    return this->name;
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
    std::cout << "name: " << this->getName() << "; record: " << this->getRecord() << "; type: " << this->getType() << std::endl;
}
