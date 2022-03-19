#include "record.h"
using st::Record;
using std::string;

Record::Record(string name, string type, string record)
    : name(std::move(name)), type(std::move(type)), record(std::move(record)) {}

[[maybe_unused]] void Record::setName(std::string _name) {
    this->name = std::move(_name);
}

[[maybe_unused]] void Record::setRecord(std::string _record) {
    this->record = std::move(_record);
}

void Record::setType(string _type) {
    this->type = std::move(_type);
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
