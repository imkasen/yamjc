#ifndef TAC_H
#define TAC_H

#include <string>

/*
 * Three Address Code
 *
 * e.g.
 *              op
 *              |
 *      x := y PLUS z
 *      |    |      |
 *   result lhs    rhs
 */
class TAC {
protected:
    std::string op;
    std::string lhs, rhs;
    std::string result;

public:
    TAC();
    TAC(std::string op, std::string lhs, std::string rhs, std::string result);
    virtual ~TAC() = default;

    void setOP(std::string _op);
    void setLHS(std::string _lhs);
    void setRHS(std::string _rhs);
    void setResult(std::string _result);

    [[nodiscard]] std::string getOP() const;
    [[nodiscard]] std::string getLHS() const;
    [[nodiscard]] std::string getRHS() const;
    [[nodiscard]] std::string getResult() const;

    [[nodiscard]] std::string printInfo() const;
};

#endif
