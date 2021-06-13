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
    if (next == childrenScopes.size()) // create new child scope
    {
        nextChild = new Scope(this);
        childrenScopes.add(nextChild);
    }
    else
    {
        nextChild = childrenScopes.get(next); // visit scope
        next++
        return nextChild;
    }
}

Scope Scope::getParentScope()
{

}

Record Scope::lookupRecord(string key) {
    if (records.containsKey(key)) // does it exist in the current scope?
    {
        return record.get(key);
    }
    else
    {
        if (parent == nullptr) // identifer not in the symbol table
        {
            return nullptr;
        }
        else 
        {
            return parent.lookup(key); // delegate the request to parent scope
        }
    }
}

void Scope::addRecord(string key, Record item)
{

}

void Scope::resetScope()
{
    next = 0;
    for (int i = 0; i < children.size(); ++i)
    {
        children.get(i).resetScope();
    }
}

void Scope::printScope()
{

}
