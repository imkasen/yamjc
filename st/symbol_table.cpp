#include "symbol_table.h"

SymbolTable::SymbolTable()
{
    root = new Scope(nullptr);
    current = root;
}

void SymbolTable::enterScope()
{
    current.nextChild(); // create new scope if needed
}

void SymbolTable::exitScope()
{
    current = current.Parent();
}

void SymbolTable::put(string key, Record item)
{
    current.put(key, item);
}

Record SymbolTable::lookup(string key)
{
    return current.lookup(key);
}

void SymbolTable::printTable()
{
    root.printScope();
}

void SymbolTable::exitScope()
{
    root.resetScope(); // preparation for new traversal
}
