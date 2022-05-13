#ifndef __TYPES_H
#define __TYPES_H

#include "symbol.h"
#include <cassert>
#include <string>

struct stmtValue;
struct exprValue;
struct callValue;
struct exprOptRptValue;
struct idlistValue;
struct forprefixValue;

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
    exprValue *next;

    exprType valType;

    operator bool() const;

    std::string type_string();
    std::string to_string();
};

struct callValue {
    exprValue *elist;
    bool method;
    std::string name;
};

struct exprOptRptValue {
    exprValue *index;
    exprValue *value;

    exprOptRptValue *next;
};

struct idlistValue {
    std::string id;
    idlistValue *next;
};

struct forprefixValue {
    unsigned long test, enter;
};

#endif /* __TYPES_H */