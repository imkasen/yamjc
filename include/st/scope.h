#ifndef ST_SCOPE_H
#define ST_SCOPE_H

#include <algorithm>
#include <deque>
#include <fstream>
#include <optional>
#include <unordered_map>
#include "record.h"

class Scope : public std::enable_shared_from_this<Scope> {
private:
    std::string scope_title;
    std::size_t next;                                                  // Next child to visit
    std::shared_ptr<Scope> parentScope;                                // Parent scope
    std::deque<std::shared_ptr<Scope>> childrenScopes;                 // Child scopes
    std::unordered_map<std::string, std::shared_ptr<Record>> records;  // Symbol to record map

public:
    Scope();
    explicit Scope(std::shared_ptr<Scope> parent);
    virtual ~Scope() = default;

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
};

#endif
