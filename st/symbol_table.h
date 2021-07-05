#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "scope.h"

class SymbolTable
{
private:
    std::shared_ptr<Scope> root;
    std::shared_ptr<Scope> current;

public:
    SymbolTable();

    void enterScope();
    void exitScope();

    void addRecord(const std::string &key, const Record &item);
    std::optional<Record> lookupRecord(const std::string &key) const;

    void printTable() const;
    void resetTable();

    virtual ~SymbolTable() = default;
};

#endif