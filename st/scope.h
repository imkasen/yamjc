#ifndef SCOPE_H
#define SCOPE_H

#include "record.h"

#include <list>
#include <map>
using std::list;
using std::map;

class Scope
{
protected:
    int next = 0;                // next child to visit
    Scope parentScope;           // parent scope
    list<Scope> childrenScopes;  // children scopes
    map<string, Record> records; // symbol to record map

public:
    Scope();

    Scope nextChild();
    Scope getParentScope();

    Record lookupRecord(string key);
    void addRecord(string, Record);
    void resetScope();
    void printScope();
};

#endif
