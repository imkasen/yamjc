#ifndef SCOPE_H
#define SCOPE_H

#include "record.h"

#include <list>
#include <unordered_map>
using std::list;
using std::unordered_map;

class Scope
{
protected:
    int next = 0; // next child to visit
    Scope parentScope; // parent scope
    list<Scope> childrenScopes; // children scopes
    unordered_map<string, Record> records; // symbol to record map

public:
    Scope nextChild();
    Record lookup(string key);
    void resetScope();

};

#endif
