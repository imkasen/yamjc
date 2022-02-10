#include "record.h"
using std::string;

Record::Record() {
    this->name = "uninitialised";
    this->type = "uninitialised";
    this->record = "Record";
}

Record::Record(string name, string type, string record)
    : name(std::move(name)), type(std::move(type)), record(std::move(record)) {}

void Record::setName(const std::string &r_name) {
    this->name = r_name;
}

void Record::setRecord(const std::string &r_record) {
    this->record = r_record;
}

void Record::setType(const string &r_type) {
    this->type = r_type;
}

string Record::getName() const {
    return this->name;
}

string Record::getType() const {
    return this->type;
}

string Record::getRecord() const {
    return this->record;
}

string Record::printRecord() const {
    return "name: " + this->getName() + "; record: " + this->getRecord() + "; type: " + this->getType();
}
