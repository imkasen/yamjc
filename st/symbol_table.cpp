#include "symbol_table.h"
using std::string;
using std::endl;

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

void SymbolTable::setScopeTitle(const std::string &title)
{
    this->current->setScopeTitle(title);
}

std::string SymbolTable::getScopeTitle() const
{
    return this->current->getScopeTitle();
}

std::shared_ptr<Scope> SymbolTable::getParentScope() const
{
    return this->current->getParentScope();
}

void SymbolTable::addRecord(const string &key, const std::shared_ptr<Record> &item)
{
    this->current->addRecord(key, item);
}

/*
 * @return std::shared_ptr<Record> | std::nullopt
 */
std::optional<std::shared_ptr<Record>> SymbolTable::lookupRecord(const string &key) const
{
    return this->current->lookupRecord(key);
}

void SymbolTable::printST(std::ofstream *outStream)
{
    *outStream << "label=\"Symbol Table\";" << endl;
    *outStream << "labelloc=\"t\";\n" << endl;
    *outStream << "node [shape=rect, fontname=Arial, width=5];\n" << endl;

    std::size_t index = 0;
    this->root->printST(index, outStream);
}

void SymbolTable::resetTable()
{
    this->root->resetScope(); // preparation for new traversal
    this->current = this->root;
}
