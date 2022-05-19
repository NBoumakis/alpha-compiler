#ifndef __TYPES_H
#define __TYPES_H

#include "symbol.h"
#include <cassert>
#include <list>
#include <string>
#include <utility>

struct stmtValue;
struct exprValue;
struct callValue;
struct exprOptRptValue;
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
    Symbol *symbolVal;
    exprValue *indexVal;
    double numConstval;
    std::string strConstVal;
    bool boolConstVal;

    exprType valType;

    unsigned long truelist, falselist;

    operator bool() const;

    std::string type_string();
    std::string to_string();

    exprValue(exprType type);
    exprValue(bool value);
    exprValue(std::string value);
    exprValue(double value);
};

struct callValue {
    exprList elist;
    bool method;
    std::string name;
};

struct exprOptRptValue {
    exprValue *index;
    exprValue *value;

    exprOptRptValue *next;
};

struct forprefixValue {
    unsigned long test, enter;
};

#endif /* __TYPES_H */