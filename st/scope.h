#ifndef SCOPE_H
#define SCOPE_H

#include "record.h"
#include <deque>
#include <map>
#include <optional>
#include <memory>

class Scope : public std::enable_shared_from_this<Scope>
{
private:
    size_t next;                                       // next child to visit
    std::shared_ptr<Scope> parentScope;                // parent scope
    std::deque<std::shared_ptr<Scope>> childrenScopes; // children scopes
    std::map<std::string, Record> records;             // symbol to record map

public:
    Scope();
    Scope(std::shared_ptr<Scope> parent);

    std::shared_ptr<Scope> getNextChild();
    std::shared_ptr<Scope> getParentScope() const;

    std::optional<Record> lookupRecord(const std::string &key) const;
    void addRecord(const std::string &key, const Record &item);
    void resetScope();
    const void printScope() const;

};

#endif
