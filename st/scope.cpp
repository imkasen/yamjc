#include "scope.h"

Scope::Scope()
{
    this->next = 0;
    this->parentScope = nullptr;
}

Scope::Scope(Scope scope)
{
    this->next = 0;
    this->parentScope = scope;
}

Scope Scope::getNextChild() {
    Scope nextChild;
    if ((this->next) == childrenScopes.size()) // create new child scope
    {
        nextChild = new Scope(*this);
        childrenScopes.push_back(nextChild);
    }
    else
    {
        (this->next)++;
        nextChild = childrenScopes.at(next); // visit scope
    }
    return nextChild;
}

Scope Scope::getParentScope()
{
    return *(this->parentScope);
}

Record Scope::lookupRecord(string key) {
    auto iterator = this->records.find(key);
    if (iterator != this->records.end()) // exist in the current scope
    {
        return iterator->second;
    }
    else
    {
        if (!(this->parentScope)) // == nullptr
        {
            return nullptr; // identifier not in the symbol table
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

void Scope::printScope()
{
    for (const auto iter : this->records)
    {
        iter.second.printRecord();
    }
}
