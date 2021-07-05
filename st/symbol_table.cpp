#include "symbol_table.h"
using std::string;

SymbolTable::SymbolTable()
{
    this->root = std::make_shared<Scope>();
    this->current = this->root;
}

void SymbolTable::enterScope()
{
    this->current = this->current->getNextChild(); // create new scope if needed
}

void SymbolTable::exitScope()
{
    this->current = this->current->getParentScope();
}

void SymbolTable::addRecord(const string &key, const Record &item)
{
    this->current->addRecord(key, item);
}

/*
 * @return Record ptr | std::nullopt
 */
std::optional<Record> SymbolTable::lookupRecord(const string &key) const
{
    return this->current->lookupRecord(key);
}

void SymbolTable::printTable() const
{
    this->root->printScope();
}

void SymbolTable::resetTable()
{
    this->root->resetScope(); // preparation for new traversal
}
