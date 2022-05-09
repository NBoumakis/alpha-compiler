#ifndef __TYPES_H
#define __TYPES_H

#include "symbol.h"
#include <string>

struct stmtValue;
struct exprValue;
struct callValue;
struct exprOptRptValue;
struct idlistValue;
struct forprefixValue;

struct stmtValue {
    unsigned long breaklist, contlist;
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

enum idlistType {
    idIdlist_T,
    idlistIdIdlist_T,
    emptyIdlist_T,
    InvalidIdlist_T
};

struct idlistValue {
    union {
        char *id;
        struct {
            idlistValue *idlistVal;
            char *idVal;
        } idlistIdValue;

    } value;

    idlistType valType;
};

struct forprefixValue {
    unsigned long test, enter;
};

#endif /* __TYPES_H */