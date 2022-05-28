#ifndef __TYPES_H
#define __TYPES_H

#include "symbol.h"
#include <list>
#include <string>
#include <utility>

struct stmtValue;
struct exprValue;
struct callValue;
struct forprefixValue;

typedef std::pair<exprValue *, exprValue *> exprPair;
typedef std::list<exprPair *> *indexedList;
typedef std::list<exprValue *> *exprList;

struct stmtValue {
    unsigned long breaklist, contlist, returnlist;
};

enum exprType {
    varExpr_T,
    TableitemExpr_T,

    userfuncExpr_T,
    libfuncExpr_T,

    arithmexprExpr_T,
    boolexprExpr_T,
    assignexprExpr_T,
    newtableExpr_T,

    constnumExpr_T,
    constboolExpr_T,
    conststringExpr_T,

    nilExpr_T,

    InvalidExpr_T
};

struct exprValue {
protected:
    Symbol *symbolVal;
    exprValue *indexVal;
    double numConstval;
    std::string strConstVal;
    bool boolConstVal;
    unsigned long truelist, falselist;
    exprType valType;

public:
    operator bool() const;

    std::string type_string() const;
    std::string to_string() const;

    exprValue(exprType type);
    exprValue(bool value);
    exprValue(std::string value);
    exprValue(double value);

    bool hasSymbol() const;

    Symbol *getSymbol() const;
    exprValue *getIndex() const;
    double getNumConst() const;
    std::string getStrConst() const;
    bool getBoolConst() const;
    unsigned long getTruelist() const;
    unsigned long getFalselist() const;

    void setSymbol(Symbol *);
    void setIndex(exprValue *);
    void setNumConst(const double);
    void setStrConst(const std::string &);
    void setBoolConst(const bool);
    void setTruelist(const unsigned long);
    void setFalselist(const unsigned long);

    bool isOperand() const;
    bool isTableitem() const;
    bool isCompileBool() const;

    bool isVariable() const;
    bool isNumber() const;
    bool isConstBool() const;
    bool isConstStr() const;
    bool isBoolExpr() const;
    bool isNil() const;
    bool isUserfunc() const;
    bool isLibfunc() const;
    bool isArithmExpr() const;
    bool isAssignExpr() const;
    bool isNewtable() const;
};

struct callValue {
    exprList elist;
    bool method;
    std::string name;
};

struct forprefixValue {
    unsigned long test, enter;
};

#endif /* __TYPES_H */