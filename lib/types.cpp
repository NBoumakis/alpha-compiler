#include "types.h"
#include "symbol.h"
#include <cassert>

exprValue::exprValue(exprType type) {
    this->valType = type;
}

exprValue::exprValue(bool value) {
    this->valType = constboolExpr_T;
    this->boolConstVal = value;
}

exprValue::exprValue(std::string value) {
    this->valType = conststringExpr_T;
    this->strConstVal = value;
}

exprValue::exprValue(double value) {
    this->valType = constnumExpr_T;
    this->numConstval = value;
}

std::string exprValue::to_string() const {
    switch (this->valType) {
    case varExpr_T:
    case TableitemExpr_T:
    case newtableExpr_T:
    case arithmexprExpr_T:
    case boolexprExpr_T:
    case assignexprExpr_T:
    case userfuncExpr_T:
    case libfuncExpr_T:
        return this->symbolVal->name;

    case constnumExpr_T:
        return std::to_string(this->numConstval);

    case constboolExpr_T:
        return ((this->boolConstVal) ? "true" : "false");

    case conststringExpr_T:
        return "\"" + this->strConstVal + "\"";

    case nilExpr_T:
        return "nil";

    case InvalidExpr_T:
        return "invalid";

    default:
        assert(false);
    }
}

std::string exprValue::type_string() const {
    std::string type_names[] = {"variable",
                                "table item",
                                "user function",
                                "library function",
                                "arithmetic expression",
                                "boolean expression",
                                "assignment expression",
                                "new table",
                                "constant number",
                                "constant boolean",
                                "constant string",
                                "nil",
                                "invalid"};

    return type_names[this->valType];
}

exprValue::operator bool() const {
    switch (this->valType) {
    case userfuncExpr_T:
    case libfuncExpr_T:
    case newtableExpr_T:
        return true;

    case constnumExpr_T:
        return this->numConstval != 0;

    case constboolExpr_T:
        return this->boolConstVal;

    case conststringExpr_T:
        return this->strConstVal != "";

    case nilExpr_T:
        return false;

    default:
        assert(false);
    }
}

bool exprValue::hasSymbol() const {
    return (this->valType == varExpr_T ||
            this->valType == TableitemExpr_T ||
            this->valType == userfuncExpr_T ||
            this->valType == libfuncExpr_T ||
            this->valType == arithmexprExpr_T ||
            this->valType == boolexprExpr_T ||
            this->valType == assignexprExpr_T ||
            this->valType == newtableExpr_T);
}

Symbol *exprValue::getSymbol() const {
    assert(hasSymbol());

    return this->symbolVal;
}

exprValue *exprValue::getIndex() const {
    assert(this->valType == TableitemExpr_T);

    return this->indexVal;
}

double exprValue::getNumConst() const {
    assert(this->valType == constnumExpr_T);

    return this->numConstval;
}
std::string exprValue::getStrConst() const {
    assert(this->valType == conststringExpr_T);

    return this->strConstVal;
}

bool exprValue::getBoolConst() const {
    assert(this->valType == constboolExpr_T);

    return this->boolConstVal;
}

unsigned long exprValue::getTruelist() const {
    return this->truelist;
}

unsigned long exprValue::getFalselist() const {
    return this->falselist;
}

void exprValue::setSymbol(Symbol *symbol) {
    assert(hasSymbol());

    this->symbolVal = symbol;
}

void exprValue::setIndex(exprValue *expr) {
    assert(this->valType == TableitemExpr_T);

    this->indexVal = expr;
}

void exprValue::setNumConst(const double num) {
    assert(this->valType == constnumExpr_T);

    this->numConstval = num;
}
void exprValue::setStrConst(const std::string &str) {
    assert(this->valType == conststringExpr_T);

    this->strConstVal = str;
}
void exprValue::setBoolConst(const bool value) {
    assert(this->valType == constboolExpr_T);

    this->boolConstVal = value;
}

void exprValue::setTruelist(const unsigned long value) {
    this->truelist = value;
}

void exprValue::setFalselist(const unsigned long value) {
    this->falselist = value;
}

bool exprValue::isOperand() const {
    return !(this->valType == userfuncExpr_T || this->valType == libfuncExpr_T ||
             this->valType == boolexprExpr_T || this->valType == newtableExpr_T ||
             this->valType == constboolExpr_T || this->valType == conststringExpr_T ||
             this->valType == nilExpr_T);
}

bool exprValue::isTableitem() const {
    return this->valType == TableitemExpr_T;
}

bool exprValue::isCompileBool() const {
    return (this->valType == nilExpr_T ||
            this->valType == libfuncExpr_T ||
            this->valType == userfuncExpr_T ||
            this->valType == constnumExpr_T ||
            this->valType == constboolExpr_T ||
            this->valType == conststringExpr_T ||
            this->valType == newtableExpr_T);
}

bool exprValue::isVariable() const {
    return this->valType == varExpr_T;
}

bool exprValue::isNumber() const {
    return this->valType == constnumExpr_T;
}

bool exprValue::isConstBool() const {
    return this->valType == constboolExpr_T;
}

bool exprValue::isConstStr() const {
    return this->valType == conststringExpr_T;
}

bool exprValue::isBoolExpr() const {
    return this->valType == boolexprExpr_T;
}

bool exprValue::isNil() const {
    return this->valType == nilExpr_T;
}

bool exprValue::isUserfunc() const {
    return this->valType == userfuncExpr_T;
}
bool exprValue::isLibfunc() const {
    return this->valType == libfuncExpr_T;
}

bool exprValue::isArithmExpr() const {
    return this->valType == arithmexprExpr_T;
}

bool exprValue::isAssignExpr() const {
    return this->valType == assignexprExpr_T;
}

bool exprValue::isNewtable() const {
    return this->valType == newtableExpr_T;
}
