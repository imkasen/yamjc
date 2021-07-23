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

    void setScopeTitle(const std::string &title);
    std::shared_ptr<Scope> getParentScope() const;

    void addRecord(const std::string &key, const std::shared_ptr<Record> &item);
    std::optional<std::shared_ptr<Record>> lookupRecord(const std::string &key) const;

    void printTable() const;
    void resetTable();

    virtual ~SymbolTable() = default;
};

#endif