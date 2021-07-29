#include "record.h"
using std::string;

Record::Record()
{
    this->name = "uninitialised";
    this->type = "uninitialised";
    this->record = "Record";
}

Record::Record(string name, string type, string record) : name(name), type(type), record(record) {}

void Record::setName(const std::string &r_name)
{
    this->name = r_name;
}

void Record::setRecord(const std::string &r_record)
{
    this->record = r_record;
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
    return this->record;
}

const std::string Record::printRecord() const
{
    return "name: " + this->getName() + "; record: " + this->getRecord() + "; type: " + this->getType();
}
