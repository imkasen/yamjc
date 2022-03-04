#ifndef CFG_TAC_H
#define CFG_TAC_H

#include <algorithm>
#include <cctype>
#include <string>
#include <utility>

namespace cfg {

/*
 * Three Address Code.
 * Example:
 *              op
 *              |
 *      x := y PLUS z
 *      |    |      |
 *   result lhs    rhs
 */
class Tac {
private:
    // used to create temporary variable names
    inline static int iid = 0;  // int
    inline static int bid = 0;  // boolean
    inline static int aid = 0;  // array
    inline static int rid = 0;  // self-defined class
    inline static int vid = 0;  // default

    std::string op;
    std::string lhs, rhs;
    std::string result;

public:
    Tac();
    Tac(std::string op, std::string lhs, std::string rhs, std::string result);
    virtual ~Tac() = default;

    void setOP(std::string _op);
    void setLHS(std::string _lhs);
    void setRHS(std::string _rhs);
    void setResult(std::string _result);
    static void resetID();

    [[nodiscard]] std::string getOP() const;
    [[nodiscard]] std::string getLHS() const;
    [[nodiscard]] std::string getRHS() const;
    [[nodiscard]] std::string getResult() const;

    static std::string generateTmpVarName(const char &type);
    [[nodiscard]] static bool isNum(const std::string &str);

    [[nodiscard]] virtual std::string printInfo() const = 0;
    [[nodiscard]] virtual std::string printBC() const = 0;
};

}  // namespace cfg

#endif
