#include "scope.h"
using std::endl;
using std::size_t;
using std::string;

Scope::Scope() {
    this->next = 0;
    this->parentScope = nullptr;
}

Scope::Scope(std::shared_ptr<Scope> parent) {
    this->next = 0;
    this->parentScope = std::move(parent);
}

void Scope::setScopeTitle(const std::string &title) {
    this->scope_title = title;
}

string Scope::getScopeTitle() const {
    // "xxx: xxx"
    size_t pos = this->scope_title.find(' ');
    if (pos != string::npos) {
        return this->scope_title.substr(pos + 1);
    } else {
        return this->scope_title;  // "Program"
    }
}

string Scope::getScopeType() const {
    size_t pos = this->scope_title.find(' ');
    if (pos != string::npos) {
        return this->scope_title.substr(0, pos - 1);  // Delete ':'
    } else {
        return this->scope_title;  // "Program"
    }
}

std::shared_ptr<Scope> Scope::getNextChild() {
    std::shared_ptr<Scope> nextChild;
    // Create new child scope
    if (this->next == this->childrenScopes.size()) {
        nextChild = std::make_shared<Scope>(shared_from_this());
        this->childrenScopes.push_back(nextChild);
    } else {
        nextChild = this->childrenScopes.at(this->next);  // Visit scope
    }
    ++(this->next);
    return nextChild;
}

std::shared_ptr<Scope> Scope::getParentScope() const {
    return this->parentScope;
}

/*
 * @return std::shared_ptr<Record> | std::nullopt
 */
std::optional<std::shared_ptr<Record>> Scope::lookupRecord(const string &key) const {  // NOLINT
    // iterator: std::unordered_map<string, std::shared_ptr<Record>>::iterator
    auto iterator = this->records.find(key);
    // Exist in the current scope
    if (iterator != this->records.end()) {
        return iterator->second;
    }
    // Key doest not exist && parent scope != nullptr
    else if (this->parentScope) {
        return this->parentScope->lookupRecord(key);  // delegate the request to parent scope
    } else {
        return std::nullopt;
    }
}

void Scope::addRecord(const string &key, const std::shared_ptr<Record> &item) {
    // ret: std::pair<std::unordered_map<string, std::shared_ptr<Record>>::iterator, bool>
    // == insert(std::pair<string, std::shared_ptr<Record>>(key, item))
    auto ret = this->records.insert({key, item});
    if (!ret.second) {  // false
        std::cerr << "The record " << key << " already exists in the scope!" << endl;
    }
}

/*
 * @return std::shared_ptr<Scope> | std::nullopt
 */
std::optional<std::shared_ptr<Scope>> Scope::lookupChildScope(const string &key) const {
    // iterator: std::deque<std::shared_ptr<Scope>>::iterator
    auto iterator = std::find_if(this->childrenScopes.begin(), this->childrenScopes.end(),
                                 [&key](const std::shared_ptr<Scope> &scope_ptr) {
                                     return scope_ptr->getScopeTitle() == key;
                                 });
    if (iterator != this->childrenScopes.end()) {
        return *iterator;
    }

    return std::nullopt;
}

void Scope::resetScope() {  // NOLINT
    for (const auto &childScope_ptr : this->childrenScopes) {
        childScope_ptr->resetScope();
    }
    this->next = 0;
}

void Scope::printST(std::size_t index, std::ofstream *outStream) {  // NOLINT
    static size_t count = index;
    string content = "<U><B>" + this->scope_title + "</B></U><BR/><BR/>\n";
    for (const auto &record_pair : this->records) {
        content += record_pair.second->printRecord() + "<BR/>\n";
    }

    // Draw
    *outStream << "n" << index << " [label=<" << content << ">];" << endl;  // HTML like labels
    for (const auto &childScope_ptr : this->childrenScopes) {
        *outStream << "n" << index << " -- n" << count + 1 << ";" << endl;
        childScope_ptr->printST(++count, outStream);
    }
}
