#ifndef SCOPE_H
#define SCOPE_H

#include "record.h"

#include <list>
#include <map>

class Scope
{
protected:
    int next;                           // next child to visit
    Scope *parentScope;                 // parent scope
    std::list<Scope *> childrenScopes;  // children scopes
    std::map<string, Record> records;   // symbol to record map

public:
    Scope();
    Scope(Scope scope);

    Scope getNextChild();
    Scope getParentScope();

    Record lookupRecord(string key);
    void addRecord(string key, Record item);
    void resetScope();
    void printScope();
};

#endif
