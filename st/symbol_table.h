#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "scope.h"

class SymbolTable
{
private:
    Scope *root;
    Scope *current;

public:
    SymbolTable();

    void enterScope();
    void exitScope();

    void addRecord(const std::string &key, Record *item);
    std::optional<Record *> lookupRecord(const std::string &key) const;

    void printTable() const;
    void resetTable();
};

#endif