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

    void addRecord(string key, Record item);
    Record lookupRecord(string key);

    void printTable();
    void resetTable();
};

#endif