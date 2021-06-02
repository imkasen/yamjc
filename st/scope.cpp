#include "scope.h"

Scope Scope::nextChild()
{
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

Record Scope::lookup(string key)
{
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

void Scope::resetScope()
{
    next = 0;
    for (int i = 0; i < children.size(); ++i)
    {
        children.get(i).resetScope();
    }
}
