#include "scope.h"
using std::string;

Scope::Scope()
{
    this->next = 0;
    this->parentScope = nullptr;
}

Scope::Scope(std::shared_ptr<Scope> parent)
{
    this->next = 0;
    this->parentScope = parent;
}

void Scope::setScopeTitle(const std::string &title)
{
    this->scope_title = title;
}

string Scope::getScopeTitle() const
{
    return this->scope_title;
}

std::shared_ptr<Scope> Scope::getNextChild()
{
    std::shared_ptr<Scope> nextChild;
    if (this->next == this->childrenScopes.size()) // create new child scope
    {
        nextChild = std::make_shared<Scope>(shared_from_this());
        this->childrenScopes.push_back(nextChild);
    }
    else
    {
        nextChild = this->childrenScopes.at(this->next); // visit scope
    }
    ++(this->next);
    return nextChild;
}

std::shared_ptr<Scope> Scope::getParentScope() const
{
    return this->parentScope;
}

/*
 * @return std::optional<Record> | std::nullopt
 */
std::optional<Record> Scope::lookupRecord(const string &key) const
{
    auto iterator = this->records.find(key);
    if (iterator != this->records.end()) // exist in the current scope
    {
        return iterator->second;
    }
    else
    {
        if (!(this->parentScope)) // == nullptr
        {
            return std::nullopt; // identifier not in the symbol table
        }
        else 
        {
            return (this->parentScope)->lookupRecord(key); // delegate the request to parent scope
        }
    }
}

void Scope::addRecord(const string &key, const std::shared_ptr<Record> &item)
{
    auto ret = this->records.insert({key, item}); // = insert(std::pair<string, std::shared_ptr<Record>>(key, item))
    if (!ret.second) // false
    {
        std::cerr << "The record " << key << " already exists in the scope!" << std::endl;
    }
}

void Scope::resetScope()
{
    for (auto iter : this->childrenScopes)
    {
        iter->resetScope();
    }
    this->next = 0;
}

const void Scope::printScope() const
{
    for (const auto &iter : this->records)
    {
        (iter.second).printRecord();
    }
}
