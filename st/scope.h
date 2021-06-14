#ifndef SCOPE_H
#define SCOPE_H

#include "record.h"

#include <deque>
#include <map>

class Scope
{
private:
    int next;                         // next child to visit
    Scope *parentScope;               // parent scope
    std::deque<Scope> childrenScopes; // children scopes
    std::map<string, Record> records; // symbol to record map

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
