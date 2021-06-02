#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "scope.h"

class SymbolTable
{
protected:
    Scope root;
    Scope current;

public:
    SymbolTable();

    void enterScope();
    void exitScope();

    void put(string key, Record item);
    Record lookup(string key);

    void printTable();
    void resetTable();
};

#endif