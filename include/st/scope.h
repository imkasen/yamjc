#ifndef SCOPE_H
#define SCOPE_H

#include "record.h"
#include <deque>
#include <unordered_map>
#include <optional>
#include <fstream>
#include <algorithm>

class Scope : public std::enable_shared_from_this<Scope>
{
private:
    std::string scope_title;
    std::size_t next;                                       // next child to visit
    std::shared_ptr<Scope> parentScope;                     // parent scope
    std::deque<std::shared_ptr<Scope>> childrenScopes;      // child scopes
    std::unordered_map<std::string, std::shared_ptr<Record>> records; // symbol to record map

public:
    Scope();
    explicit Scope(std::shared_ptr<Scope> parent);

    void setScopeTitle(const std::string &title);
    std::string getScopeTitle() const;
    std::string getScopeType() const;

    std::shared_ptr<Scope> getNextChild();
    std::shared_ptr<Scope> getParentScope() const;

    std::optional<std::shared_ptr<Record>> lookupRecord(const std::string &key) const;
    void addRecord(const std::string &key, const std::shared_ptr<Record> &item);

    std::optional<std::shared_ptr<Scope>> lookupChildScope(const std::string &key) const;

    void resetScope();
    void printST(std::size_t index, std::ofstream *outStream);

    virtual ~Scope() = default;
};

#endif
