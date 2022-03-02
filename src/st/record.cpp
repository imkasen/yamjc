#include "record.h"
using st::Record;
using std::string;

Record::Record() {
    this->name = "uninitialised";
    this->type = "uninitialised";
    this->record = "Record";
    // this->value = "";  // leave as empty
}

Record::Record(string name, string type, string record)
    : name(std::move(name)), type(std::move(type)), record(std::move(record)) {}

void Record::setName(std::string _name) {
    this->name = std::move(_name);
}

void Record::setRecord(std::string _record) {
    this->record = std::move(_record);
}

void Record::setType(string _type) {
    this->type = std::move(_type);
}

void Record::setValue(string _value) {
    this->value = std::move(_value);
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

string Record::getValue() const {
    return this->value;
}

string Record::printRecord() const {
    return "name: " + this->getName() + "; record: " + this->getRecord() + "; type: " + this->getType();
}
