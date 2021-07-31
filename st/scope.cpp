#include "scope.h"
using std::string;
using std::size_t;
using std::endl;

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

const string Scope::getScopeTitle() const
{
    // "xxx: xxx"
    size_t pos = this->scope_title.find(" ");
    if (pos != string::npos)
    {
        return this->scope_title.substr(pos + 1);
    }
    else
    {
        return this->scope_title; // "Program"
    }
}

const string Scope::getScopeType() const
{
    size_t pos = this->scope_title.find(" ");
    if (pos != string::npos)
    {
        return this->scope_title.substr(0, pos - 1);
    }
    else
    {
        return this->scope_title; // "Program"
    }
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
 * @return std::shared_ptr<Record> | std::nullopt
 */
std::optional<std::shared_ptr<Record>> Scope::lookupRecord(const string &key) const
{
    auto iterator = this->records.find(key);
    if (iterator != this->records.end()) // exist in the current scope
    {
        return iterator->second;
    }
    else if (this->parentScope) // key doest not exist && parent scope != nullptr
    {
        return this->parentScope->lookupRecord(key); // delegate the request to parent scope
    }
    else
    {
        return std::nullopt;
    }
}

void Scope::addRecord(const string &key, const std::shared_ptr<Record> &item)
{
    auto ret = this->records.insert({key, item}); // = insert(std::pair<string, std::shared_ptr<Record>>(key, item))
    if (!ret.second) // false
    {
        std::cerr << "The record " << key << " already exists in the scope!" << endl;
    }
}

void Scope::resetScope()
{
    for (auto ptr : this->childrenScopes)
    {
        ptr->resetScope();
    }
    this->next = 0;
}

void Scope::printST(std::size_t index, std::ofstream *outStream)
{
    static size_t count = index;
    string content = "<U><B>" + this->scope_title + "</B></U><BR/><BR/>\n";
    for (const auto pair : records)
    {
        content += pair.second->printRecord() + "<BR/>\n";
    }

    // draw
    *outStream << "n" << index << " [label=<" << content << ">];" << endl; // HTML like labels
    for (const auto childScope : childrenScopes)
    {
        *outStream << "n" << index << " -- n" << count + 1 << ";" << endl;
        childScope->printST(++count, outStream);
    }
}
