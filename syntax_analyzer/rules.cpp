#include "rules.h"
#include "colors.h"
#include "scope_space.h"
#include "symbol.h"
#include "symbol_table.h"
#include <cassert>
#include <iostream>
#include <set>
#include <string>

extern int yylineno;

std::string type_names[] = {
    std::string("global variable"),
    std::string("local variable"),
    std::string("formal argument"),
    std::string("user function"),
    std::string("library function")};

static inline SymbolType var_type() {
    if (scopeLevel == 0) {
        return GLOBAL_VAR;
    } else {
        return LOCAL_VAR;
    }
}

programValue *Manage_program(stmtListValue *stmtList) {
    programValue *newStructVal;
    return newStructVal;
}

stmtListValue *Manage_stmtList_stmt(stmtListValue *stmtList, stmtValue *stmt) {
    stmtListValue *stmtListVal;
    return stmtListVal;
}

stmtListValue *Manage_stmtList() {
    stmtListValue *stmtListVal;
    return stmtListVal;
}

/* Statements */
stmtValue *Manage_stmt_expr(exprValue *expr) {
    stmtValue *stmtValueVal;
    return stmtValueVal;
}

stmtValue *Manage_stmt_ifstmt(ifstmtValue *ifstmt) {
    stmtValue *stmtValueVal;
    return stmtValueVal;
}

stmtValue *Manage_stmt_whilestmt(whilestmtValue *whilestmt) {
    stmtValue *stmtValueVal;
    return stmtValueVal;
}

stmtValue *Manage_stmt_forstmt(forstmtValue *forstmt) {
    stmtValue *stmtValueVal;
    return stmtValueVal;
}

stmtValue *Manage_stmt_returnstmt(returnstmtValue *returnstmt) {
    stmtValue *stmtValueVal;
    return stmtValueVal;
}

stmtValue *Manage_stmt_break() {
    stmtValue *stmtValueVal;
    return stmtValueVal;
}

stmtValue *Manage_stmt_continue() {
    stmtValue *stmtValueVal;
    return stmtValueVal;
}

stmtValue *Manage_stmt_block(blockValue *block) {
    stmtValue *stmtValueVal;
    return stmtValueVal;
}

stmtValue *Manage_stmt_funcdef(funcdefValue *funcdef) {
    stmtValue *stmtValueVal;
    return stmtValueVal;
}

stmtValue *Manage_stmt_semicolon() {
    stmtValue *stmtValueVal;
    return stmtValueVal;
}

/* Expressions */
exprValue *Manage_expr_assignexpr(exprValue *assignexpr) {
    exprValue *exprValueVal;
    return exprValueVal;
}

exprValue *Manage_expr_expr_PLUS_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *exprValueVal;
    return exprValueVal;
}

exprValue *Manage_expr_expr_MINUS_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *exprValueVal;
    return exprValueVal;
}

exprValue *Manage_expr_expr_MUL_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *exprValueVal;
    return exprValueVal;
}

exprValue *Manage_expr_expr_DIV_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *exprValueVal;
    return exprValueVal;
}

exprValue *Manage_expr_expr_MOD_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *exprValueVal;
    return exprValueVal;
}

exprValue *Manage_expr_expr_GT_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *exprValueVal;
    return exprValueVal;
}

exprValue *Manage_expr_expr_GE_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *exprValueVal;
    return exprValueVal;
}

exprValue *Manage_expr_expr_LT_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *exprValueVal;
    return exprValueVal;
}

exprValue *Manage_expr_expr_LE_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *exprValueVal;
    return exprValueVal;
}

exprValue *Manage_expr_expr_EQUAL_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *exprValueVal;
    return exprValueVal;
}

exprValue *Manage_expr_expr_NEQUAL_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *exprValueVal;
    return exprValueVal;
}

exprValue *Manage_expr_expr_AND_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *exprValueVal;
    return exprValueVal;
}

exprValue *Manage_expr_expr_OR_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *exprValueVal;
    return exprValueVal;
}

exprValue *Manage_expr_term(exprValue *term) {
    exprValue *exprValueVal;
    return exprValueVal;
}

/* Terms */
exprValue *Manage_term_LPexprRP(exprValue *expr) {
    exprValue *termValueVal;
    return termValueVal;
}

exprValue *Manage_term_notexpr(exprValue *expr) {
    exprValue *termValueVal;
    return termValueVal;
}

exprValue *Manage_term_PPlval(exprValue *lvalue) {
    exprValue *termValueVal;

    if (lvalue->valType == varExpr_T) {
        if (lvalue->symbolVal->type == USER_FUNC ||
            lvalue->symbolVal->type == LIB_FUNC) {
            std::cerr << BRED "Invalid preincrement of "
                      << type_names[lvalue->symbolVal->type]
                      << " \"" << lvalue->symbolVal->name
                      << "\" in line " << yylineno << "." RST << std::endl;
        }
    }

    return termValueVal;
}

exprValue *Manage_term_lvaluePP(exprValue *lvalue) {
    exprValue *termValueVal;

    if (lvalue->valType == varExpr_T) {
        if (lvalue->symbolVal->type == USER_FUNC ||
            lvalue->symbolVal->type == LIB_FUNC) {
            std::cerr << BRED "Invalid postincrement of "
                      << type_names[lvalue->symbolVal->type]
                      << " \"" << lvalue->symbolVal->name
                      << "\" in line " << yylineno << "." RST << std::endl;
        }
    }

    return termValueVal;
}

exprValue *Manage_term_MMlval(exprValue *lvalue) {
    exprValue *termValueVal;

    if (lvalue->valType == varExpr_T) {
        if (lvalue->symbolVal->type == USER_FUNC ||
            lvalue->symbolVal->type == LIB_FUNC) {
            std::cerr << BRED "Invalid predecrement of "
                      << type_names[lvalue->symbolVal->type]
                      << " \"" << lvalue->symbolVal->name
                      << "\" in line " << yylineno << "." RST << std::endl;
        }
    }

    return termValueVal;
}

exprValue *Manage_term_lvalueMM(exprValue *lvalue) {
    exprValue *termValueVal;

    if (lvalue->valType == varExpr_T) {
        if (lvalue->symbolVal->type == USER_FUNC ||
            lvalue->symbolVal->type == LIB_FUNC) {
            std::cerr << BRED "Invalid postdecrement of "
                      << type_names[lvalue->symbolVal->type]
                      << " \"" << lvalue->symbolVal->name
                      << "\" in line " << yylineno << "." RST << std::endl;
        }
    }

    return termValueVal;
}

exprValue *Manage_term_primary(exprValue *primary) {
    exprValue *termValueVal;
    return termValueVal;
}

exprValue *Manage_term_minusexpr(exprValue *expr) {
    exprValue *termValueVal;
    return termValueVal;
}

/* Assign expression */
exprValue *Manage_assignexpr_lvalueASSIGNexpr(exprValue *lvalue, exprValue *expr) {
    exprValue *newStructVal = new exprValue();

    Symbol *symbol;
    unsigned int i;

    newStructVal->valType = InvalidExpr_T;

    if (lvalue->valType == varExpr_T) {
        symbol = lvalue->symbolVal;

        if (symbol->type == USER_FUNC ||
            symbol->type == LIB_FUNC) {
            std::cerr << BRED "Cannot assign to " << type_names[symbol->type] << " \"" << symbol->name << "\" in line " << yylineno << RST << std::endl;
        } else if (funcDepth != symbol->funcDepth && symbol->type != GLOBAL_VAR) {
            std::cerr << BRED "Inaccessible " << type_names[symbol->type] << " \"" << symbol->name << "\" in line " << yylineno << RST << std::endl;
        } else {
            newStructVal->valType = assignexprExpr_T;
            newStructVal->symbolVal = lvalue->symbolVal;
            /*newStructVal-> = expr;*/
        }
    }

    return newStructVal;
}

/* Primary */
exprValue *Manage_primary_lvalue(exprValue *lvalue) {
    exprValue *primaryValueVal = new exprValue();

    primaryValueVal->valType = InvalidExpr_T;

    if (lvalue->valType == varExpr_T) {
        Symbol *symbol = lvalue->symbolVal;
        if (symbol->scope == 0 ||
            symbol->type == USER_FUNC ||
            symbol->type == LIB_FUNC ||
            funcDepth == symbol->funcDepth) {
            primaryValueVal->valType = varExpr_T;
            primaryValueVal->symbolVal = lvalue->symbolVal;
        } else {
            std::cerr << BRED "Inaccessible " << type_names[symbol->type] << " \"" << symbol->name << "\" in line " << yylineno << RST << std::endl;
        }
    }

    return primaryValueVal;
}

exprValue *Manage_primary_call(exprValue *call) {
    exprValue *primaryValueVal;
    return primaryValueVal;
}

exprValue *Manage_primary_objectdef(exprValue *objdef) {
    exprValue *primaryValueVal;
    return primaryValueVal;
}

exprValue *Manage_primary_LPfuncdefRP(funcdefValue *funcdef) {
    exprValue *primaryValueVal;
    return primaryValueVal;
}

exprValue *Manage_primary_const(exprValue *constVal) {
    exprValue *primaryValueVal;
    return primaryValueVal;
}

/* lvalue */
static exprValue *lvalue_expr(Symbol *symbol) {
    assert(symbol);

    exprValue *e = new exprValue();

    e->symbolVal = symbol;
    e->next = nullptr;

    switch (symbol->type) {
    case VARIABLE:
        e->valType = varExpr_T;
        break;

    case USER_FUNC:
        e->valType = userfuncExpr_T;
        break;

    case LIB_FUNC:
        e->valType = libfuncExpr_T;
        break;

    default:
        assert(false);
    }

    return e;
}

exprValue *Manage_lvalue_id(std::string id) {
    size_t i;
    Symbol *symbol = nullptr;

    for (i = scopeLevel + 1; i > 0 && symbol == nullptr; --i) {
        symbol = symbolTableObj.lookup_scope(id, i - 1);
    }

    if (symbol == nullptr) {
        symbol = new Variable(id, scopeLevel, yylineno, funcDepth, currScopespace(), currScopespaceOffset());
        symbolTableObj.insert(id, symbol, scopeLevel);

        increaseCurrScopeOffset();
    }

    assert(symbol);

    return lvalue_expr(symbol);
}

exprValue *Manage_lvalue_localid(std::string id) {
    exprValue *newStructVal = new exprValue();
    unsigned int &scope = scopeLevel;

    auto symbol_in_table = symbolTableObj.lookup_scope(id, scope);

    if (symbol_in_table == nullptr) {
        if (!isLibFunction(id)) {
            symbol_in_table = new Variable(id, scope, yylineno, funcDepth, var_type());
            symbolTableObj.insert(id, symbol_in_table, scope);

            newStructVal->symbolVal = symbol_in_table;
            newStructVal->valType = varExpr_T;
        } else {
            std::cerr << BRED "Variable \"" << id << "\" in line " << yylineno
                      << " attempts to shadow library function." RST << std::endl;

            newStructVal->valType = InvalidExpr_T;
        }
    } else {

        newStructVal->symbolVal = symbol_in_table;
        newStructVal->valType = varExpr_T;
    }

    assert((newStructVal->valType == InvalidExpr_T) || (newStructVal->valType == varExpr_T && newStructVal->symbolVal));

    return newStructVal;
}

exprValue *Manage_lvalue_globalid(std::string id) {
    exprValue *newStructVal = new exprValue();

    auto symbol = symbolTableObj.lookup_scope(id, 0);

    if (symbol == nullptr) {
        std::cerr << BRED "Undefined reference to global symbol \"" << id << "\" in line " << yylineno << "." RST << std::endl;
        newStructVal->valType = InvalidExpr_T;
    } else {
        newStructVal->valType = varExpr_T;
        newStructVal->symbolVal = symbol;
    }

    return newStructVal;
}

exprValue *Manage_lvalue_member(exprValue *member) {
    exprValue *lvalueValueVal;
    return lvalueValueVal;
}

/* Members */
exprValue *Manage_member_lvalueDOTid(exprValue *lvalue, std::string id) {
    exprValue *memberVal;
    return memberVal;
}

exprValue *Manage_member_lvalueLSBexprRSB(exprValue *lvalue, exprValue *expr) {
    exprValue *memberVal;
    return memberVal;
}

exprValue *Manage_member_callDOTid(exprValue *call, std::string id) {
    exprValue *memberVal;
    return memberVal;
}

exprValue *Manage_member_callLSBexprRSB(exprValue *call, exprValue *expr) {
    exprValue *memberVal;
    return memberVal;
}

/* Calls */
exprValue *Manage_call_callLPelistRP(exprValue *call, elistValue *elist) {
    exprValue *callVal;
    return callVal;
}

exprValue *Manage_call_lvaluecallsuffix(exprValue *lvalue, callsuffixValue *callsuffix) {
    exprValue *callVal;

    callVal->valType = varExpr_T;

    // TODO
    /*if (lvalue->valType == SymbolLvalue_T) {
        callVal->valType = lvalueCallSuffCall_T;
        callVal->callLvalueValue.lvalueVal = lvalue;
        callVal->callLvalueValue.callsuffixVal = callsuffix;
    }*/

    return callVal;
}

exprValue *Manage_call_LPfuncdefRPLPelistRP(funcdefValue *funcdef, elistValue *elist) {
    exprValue *callVal;
    return callVal;
}

/* Call suffix */
callsuffixValue *Manage_callsuffix_normcall(normcallValue *normcall) {
    callsuffixValue *newStructVal;
    return newStructVal;
}

callsuffixValue *Manage_callsuffix_methodcall(methodcallValue *methodcall) {
    callsuffixValue *newStructVal;
    return newStructVal;
}

/* Normal call */
normcallValue *Manage_normcall_LPelistRP(elistValue *elist) {
    normcallValue *newStructVal;
    return newStructVal;
}

/* Method call */
methodcallValue *Manage_methodcall_DDOTidLPelistRP(std::string id, elistValue *elist) {
    methodcallValue *newStructVal;
    return newStructVal;
}

/* elist */
elistValue *Manage_elist_exprOptRpt(exprOptRptValue *exprOptRpt) {
    elistValue *newStructVal;
    return newStructVal;
}

elistValue *Manage_elist() {
    elistValue *newStructVal;
    return newStructVal;
}

/* Expression optional and repeatable */
exprOptRptValue *Manage_exprOR_exprOR(exprValue *expr, exprOptRptValue *exprOptRpt) {
    exprOptRptValue *newStructVal;
    return newStructVal;
}

exprOptRptValue *Manage_exprOR_expr(exprValue *expr) {
    exprOptRptValue *newStructVal;
    return newStructVal;
}

/* Objectdef */
exprValue *Manage_objectdef_LSBelistRSB(elistValue *elist) {
    exprValue *newStructVal;
    return newStructVal;
}

exprValue *Manage_objectdef_LSBindexedRSB(indexedValue *indexed) {
    exprValue *newStructVal;
    return newStructVal;
}

/* Indexed */
indexedValue *Manage_indexed(indelemlistValue *indelemlist) {
    indexedValue *newStructVal;
    return newStructVal;
}

/* Indexed element list */
indelemlistValue *Manage_indelemlist(indexedelemValue *indexedelem, indelemlistValue *indelemlist) {
    indelemlistValue *newStructVal;
    return newStructVal;
}

indelemlistValue *Manage_indelemlist_indexedelem(indexedelemValue *indexedelem) {
    indelemlistValue *newStructVal;
    return newStructVal;
}

indexedelemValue *Manage_indexedelem_LCB_expr_COLON_expr_RCB(exprValue *key, exprValue *value) {
    indexedelemValue *newStructVal;
    return newStructVal;
}

/* Block */
blockValue *Manage_block_LCBstmtRCB(stmtListValue *stmt) {
    /*  1){ scope++
        2)hide(scope);scope--}*/
    blockValue *newStructVal;
    return newStructVal;
}

/* Funcdef */
Symbol *Manage_funcprefix(std::string funcName) {
    Symbol *newFunc = new Function(funcName, scopeLevel, yylineno, funcDepth, USER_FUNC);

    if (isLibFunction(funcName)) {
        std::cerr << BRED "Cannot define function \"" << funcName << "\" in line " << yylineno
                  << ". It would shadow a library function." RST << std::endl;

        return nullptr;
    }

    auto symbol_in_table = symbolTableObj.lookup_scope(funcName, scopeLevel);

    if (symbol_in_table != nullptr) {
        std::cerr << BRED "Cannot define function \"" << funcName
                  << "\" in line " << yylineno << ". It shadows previous "
                  << type_names[symbol_in_table->type] << " defined in line "
                  << symbol_in_table->line << "." RST << std::endl;

        return nullptr;
    } else {
        symbolTableObj.insert(funcName, newFunc, scopeLevel);
    }

    return newFunc;
}

static bool check_funcargs(idlistValue *idlist) {
    std::set<std::string> argSet;

    while (idlist->valType == idlistIdIdlist_T) {
        std::string id = idlist->value.idlistIdValue.idVal;

        auto symbol_in_table = symbolTableObj.lookup_scope(id, scopeLevel);

        if (argSet.count(id) > 0) {
            std::cerr << BRED "Duplicate argument \"" << id << "\" in line " << yylineno << RST << std::endl;

            return false;
        } else if (isLibFunction(id)) {
            std::cerr << BRED "Formal argument \"" << id << "\" in line " << yylineno
                      << " attempts to shadow a library function." RST << std::endl;

            return false;
        } else if (symbol_in_table != nullptr) {
            std::cerr << BRED "Formal argument \"" << id << "\" in line "
                      << yylineno << " attempts to shadow with previous "
                      << type_names[symbol_in_table->type] << " defined in line "
                      << symbol_in_table->line << "." RST << std::endl;

            return false;
        }

        argSet.insert(id);
        idlist = idlist->value.idlistIdValue.idlistVal;
    }

    if (idlist->valType == idIdlist_T) {
        std::string id = idlist->value.id;

        auto symbol_in_table = symbolTableObj.lookup_scope(id, scopeLevel);

        if (argSet.count(id) > 0) {
            std::cerr << BRED "Duplicate argument \"" << id << "\" in line " << yylineno << RST << std::endl;

            return false;
        } else if (isLibFunction(id)) {
            std::cerr << BRED "Formal argument \"" << id << "\" in line " << yylineno
                      << " shadows a library function." RST << std::endl;

            return false;
        } else if (symbol_in_table != nullptr) {
            std::cerr << BRED "Formal argument \"" << id << "\" in line "
                      << yylineno << " attempts to shadow previous "
                      << type_names[symbol_in_table->type] << " defined in line "
                      << symbol_in_table->line << "." RST << std::endl;

            return false;
        }
    }

    return true;
}

void Manage_funcargs(idlistValue *idlist) {
    idlistValue *idlist_ptr = idlist;
    ++scopeLevel;

    if (check_funcargs(idlist)) {
        while (idlist_ptr->valType == idlistIdIdlist_T) {
            Symbol *newArg = new Variable(idlist_ptr->value.idlistIdValue.idVal, scopeLevel, yylineno, funcDepth, FORMAL_ARG);

            symbolTableObj.insert(newArg->name, newArg, scopeLevel);

            idlist_ptr = idlist_ptr->value.idlistIdValue.idlistVal;
        }

        if (idlist_ptr->valType == idIdlist_T) {
            Symbol *newArg = new Variable(idlist_ptr->value.id, scopeLevel, yylineno, funcDepth, FORMAL_ARG);

            symbolTableObj.insert(newArg->name, newArg, scopeLevel);
        }
    }

    --scopeLevel;
}

funcdefValue *Manage_funcdef_id(std::string id, idlistValue *idlist, blockValue *block) {
    funcdefValue *fval = new funcdefValue();
    unsigned int &scope = scopeLevel;

    if (isLibFunction(id)) {
        std::cerr << BRED "Cannot define function \"" << id << "\" in line "
                  << yylineno << ". It would shadow a library function." RST << std::endl;

        fval->valType = InvalidFuncdef_T;
        return fval;
    }

    auto symbol_in_table = symbolTableObj.lookup_scope(id, scope);

    if (symbol_in_table != nullptr) {
        std::cerr << BRED "Cannot define function \"" << id << "\" in line " << yylineno << ". It shadows previous "
                  << type_names[symbol_in_table->type] << " defined in line "
                  << symbol_in_table->line << "." RST << std::endl;

        fval->valType = InvalidFuncdef_T;
        return fval;
    }

    Symbol *newFunc = new Function(id, scope, yylineno, funcDepth, USER_FUNC);
    symbolTableObj.insert(id, newFunc, scope);

    return fval;
}

funcdefValue *Manage_funcdef(idlistValue *idlist, blockValue *block) {
    static unsigned long long unnamed_function_counter = 0;

    std::string function_name = std::string("$f") + std::to_string(unnamed_function_counter);

    return Manage_funcdef_id(function_name, idlist, block);
}

std::string newTmpFuncname() {
    static unsigned long long unnamed_function_counter = 0;

    std::string function_name = std::string("$f") + std::to_string(unnamed_function_counter++);

    return function_name;
}

/* Constants */
exprValue *Manage_const_int(int intVal) {
    exprValue *newStructVal;
    return newStructVal;
}

exprValue *Manage_const_real(double doubleVal) {
    exprValue *newStructVal;
    return newStructVal;
}

exprValue *Manage_const_string(std::string strVal) {
    exprValue *newStructVal;
    return newStructVal;
}

exprValue *Manage_const_nil() {
    exprValue *newStructVal;
    return newStructVal;
}

exprValue *Manage_const_true() {
    exprValue *newStructVal;
    return newStructVal;
}

exprValue *Manage_const_false() {
    exprValue *newStructVal;
    return newStructVal;
}

/* ID list */
idlistValue *Manage_idlist_ID(std::string id) {
    idlistValue *newStructVal = new idlistValue();

    newStructVal->valType = idIdlist_T;

    newStructVal->value.id = new char[id.length()];
    std::size_t length = id.copy(newStructVal->value.id, id.length());
    newStructVal->value.id[length] = '\0';

    return newStructVal;
}

idlistValue *Manage_idlist_idlist_comma_id(idlistValue *idlist, std::string id) {
    idlistValue *newStructVal = new idlistValue();

    newStructVal->valType = idlistIdIdlist_T;
    newStructVal->value.idlistIdValue.idVal = new char[id.length()];
    std::size_t length = id.copy(newStructVal->value.idlistIdValue.idVal, id.length());
    newStructVal->value.idlistIdValue.idVal[length] = '\0';

    newStructVal->value.idlistIdValue.idlistVal = idlist;

    return newStructVal;
}

idlistValue *Manage_idlist() {
    idlistValue *newStructVal = new idlistValue();

    newStructVal->valType = emptyIdlist_T;

    return newStructVal;
}

/* If statement */
ifstmtValue *Manage_ifstmt(exprValue *expr, stmtValue *stmt, elseValue *elseVal) {
    ifstmtValue *newStructVal;
    return newStructVal;
}

/* else */
elseValue *Manage_else_stmt(stmtValue *stmt) {
    elseValue *newStructVal;
    return newStructVal;
}

elseValue *Manage_else() {
    elseValue *newStructVal;
    return newStructVal;
}

/* While statement */
whilestmtValue *Manage_whilestmt(exprValue *expr, stmtValue *stmt) {
    whilestmtValue *newStructVal;
    return newStructVal;
}

/* For statement */
forstmtValue *Manage_for(elistValue *elistFirst, exprValue *expr, elistValue *elistLast, stmtValue *stmt) {
    forstmtValue *newStructVal;
    return newStructVal;
}

/* Return statement */
returnstmtValue *Manage_returnstmt(retValue *ret) {
    returnstmtValue *newStructVal;

    if (funcDepth == 0) {
        std::cerr << BRED "Cannot use return statement outside of function in line " << yylineno << RST << std::endl;
    }

    return newStructVal;
}

/* Return */
retValue *Manage_ret_expr(exprValue *expr) {
    retValue *newStructVal;
    return newStructVal;
}

retValue *Manage_ret() {
    retValue *newStructVal;
    return newStructVal;
}