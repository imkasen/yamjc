#ifndef ST_SYMBOL_TABLE_H
#define ST_SYMBOL_TABLE_H

#include "scope.h"

namespace st {

class SymbolTable {
private:
    std::shared_ptr<Scope> root;
    std::shared_ptr<Scope> current;

public:
    SymbolTable();
    virtual ~SymbolTable() = default;

    void enterScope();
    void exitScope();

    void setScopeTitle(const std::string &title);
    [[nodiscard]] std::string getScopeTitle() const;
    [[nodiscard]] std::string getScopeType() const;
    [[nodiscard]] std::shared_ptr<Scope> getParentScope() const;

    void addRecord(const std::string &key, const std::shared_ptr<Record> &item);
    [[nodiscard]] std::optional<std::shared_ptr<Record>> lookupRecord(const std::string &key) const;
    [[nodiscard]] std::optional<std::shared_ptr<Record>> lookupRecordInRoot(const std::string &key) const;

    [[nodiscard]] std::optional<std::shared_ptr<Scope>> lookupChildScope(const std::string &key) const;

    void printST(std::ofstream* outStream);
    void resetTable();
};

}  // namespace st

#endif