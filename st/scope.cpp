#include "scope.h"

Scope::Scope()
{
    this->next = 0;
    this->parentScope = nullptr;
}

Scope::Scope(Scope *scope_ptr)
{
    this->next = 0;
    this->parentScope = scope_ptr;
}

Scope* Scope::getNextChild()
{
    Scope *nextChild;
    if (this->next == this->childrenScopes.size()) // create new child scope
    {
        nextChild = new Scope(this);
        this->childrenScopes.push_back(nextChild);
    }
    else
    {
        nextChild = this->childrenScopes.at((this->next)++); // visit scope
    }
    return nextChild;
}

Scope* Scope::getParentScope() const
{
    return this->parentScope;
}

optional<Record> Scope::lookupRecord(string key) const
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
            return nullopt; // identifier not in the symbol table
        }
        else 
        {
            return (this->parentScope)->lookupRecord(key); // delegate the request to parent scope
        }
    }
}

void Scope::addRecord(string key, Record item)
{
    this->records.insert(std::pair<string, Record>(key, item));
}

void Scope::resetScope()
{
    for (Scope iter : this->childrenScopes)
    {
        iter.resetScope();
    }
    this->next = 0;
}

const void Scope::printScope() const
{
    for (const auto iter : this->records)
    {
        iter.second.printRecord();
    }
}
