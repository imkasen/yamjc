#include "symbol_table.h"
using st::Record;
using st::Scope;
using st::SymbolTable;
using std::endl;
using std::string;

SymbolTable::SymbolTable() {
    this->root = std::make_shared<Scope>();
    this->current = this->root;
}

void SymbolTable::enterScope() {
    this->current = this->current->getNextChild();  // Create new scope if needed
}

void SymbolTable::exitScope() {
    if (this->current) {
        this->current = this->current->getParentScope();
    }
}

void SymbolTable::setScopeTitle(const std::string &title) {
    this->current->setScopeTitle(title);
}

string SymbolTable::getScopeTitle() const {
    return this->current->getScopeTitle();
}

string SymbolTable::getScopeType() const {
    return this->current->getScopeType();
}

std::shared_ptr<Scope> SymbolTable::getParentScope() const {
    return this->current->getParentScope();
}

void SymbolTable::addRecord(const string &key, const std::shared_ptr<Record> &item) {
    this->current->addRecord(key, item);
}

/*
 * @return std::shared_ptr<Record> | std::nullopt
 */
std::optional<std::shared_ptr<Record>> SymbolTable::lookupRecord(const string &key) const {
    return this->current->lookupRecord(key);
}

/*
 * Search class in "Program" scope
 * @return std::shared_ptr<Record> | std::nullopt
 */
std::optional<std::shared_ptr<Record>> SymbolTable::lookupRecordInRoot(const std::string &key) const {
    return this->root->lookupRecord(key);
}

std::optional<std::shared_ptr<Scope>> SymbolTable::lookupChildScope(const string &key) const {
    return this->current->lookupChildScope(key);
}

void SymbolTable::printST(std::ofstream &ostream) {
    std::size_t index = 0;
    this->root->printST(index, ostream);
}

void SymbolTable::resetTable() {
    this->root->resetScope();  // Preparation for a new traversal
    this->current = this->root;
}
