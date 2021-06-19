#ifndef SCOPE_H
#define SCOPE_H

#include "record.h"
#include <deque>
#include <map>
#include <optional>
using std::optional;
using std::nullopt;

class Scope
{
private:
    int next;                           // next child to visit
    Scope *parentScope;                 // parent scope
    std::deque<Scope *> childrenScopes; // children scopes
    std::map<string, Record> records;   // symbol to record map

public:
    Scope();
    Scope(Scope *scope_ptr);

    Scope* getNextChild();
    Scope* getParentScope() const;

    optional<Record> lookupRecord(string key) const;
    void addRecord(string key, Record item);
    void resetScope();
    const void printScope() const;
};

#endif
