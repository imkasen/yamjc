#ifndef SCOPE_H
#define SCOPE_H

#include "record.h"
#include <deque>
#include <map>
#include <optional>
#include <utility>

class Scope
{
private:
    size_t next;                             // next child to visit
    Scope *parentScope;                      // parent scope
    std::deque<Scope *> childrenScopes;      // children scopes
    std::map<std::string, Record *> records; // symbol to record map

public:
    Scope();
    Scope(Scope *scope_ptr);

    Scope* getNextChild();
    Scope* getParentScope() const;

    std::optional<Record *> lookupRecord(const std::string &key) const;
    void addRecord(const std::string &key, Record *item);
    void resetScope();
    const void printScope() const;

    virtual ~Scope() = default;
};

#endif
