#include "rules.h"
#include "colors.h"
#include "icode.h"
#include "scope_space.h"
#include "symbol.h"
#include "symbol_table.h"
#include "temp_vars.h"
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

static exprValue *make_call(exprValue *lvalue, exprValue *elist_r) {
    exprValue *func = emit_iftableitem(lvalue);

    while (elist_r) {
        emit(param_iop, elist_r, NULL, NULL);
        elist_r = elist_r->next;
    }

    emit(call_iop, func, NULL, NULL);

    exprValue *result = new exprValue();
    result->valType = varExpr_T;

    result->symbolVal = newTempvar();
    emit(get_retval_iop, NULL, NULL, result);

    return result;
}

static exprValue *member_item(exprValue *lvalue, std::string name) {
    lvalue = emit_iftableitem(lvalue);

    exprValue *tableitem = new exprValue();
    tableitem->valType = TableitemExpr_T;
    tableitem->symbolVal = lvalue->symbolVal;

    tableitem->indexVal = new exprValue();
    tableitem->indexVal->valType = conststringExpr_T;
    tableitem->indexVal->strConstVal = name;

    return tableitem;
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

stmtValue *Manage_stmt_funcdef(Function *funcdef) {
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
    exprValue *assignexprVal;

    unsigned int i;

    if (lvalue->valType == varExpr_T) {
        Symbol *symbol = lvalue->symbolVal;

        if (symbol->type == USER_FUNC ||
            symbol->type == LIB_FUNC) {
            std::cerr << BRED "Cannot assign to " << type_names[symbol->type] << " \"" << symbol->name << "\" in line " << yylineno << RST << std::endl;
        } else if (funcDepth != symbol->funcDepth &&
                   symbol->type == VARIABLE && static_cast<Variable *>(symbol)->space != GLOBAL_VAR) {
            std::cerr << BRED "Inaccessible " << type_names[symbol->type] << " \"" << symbol->name << "\" in line " << yylineno << RST << std::endl;
        } else {
            emit(assign_iop, expr, nullptr, lvalue);

            assignexprVal = new exprValue();
            assignexprVal->valType = assignexprExpr_T;

            assignexprVal->symbolVal = newTempvar();
            emit(assign_iop, lvalue, NULL, assignexprVal);
        }
    } else if (lvalue->valType == TableitemExpr_T) {
        emit(table_setelem_iop, lvalue, lvalue->indexVal, expr);

        assignexprVal = emit_iftableitem(lvalue);
        assignexprVal->valType = assignexprExpr_T;
    }

    return assignexprVal;
}

/* Primary */
exprValue *Manage_primary_lvalue(exprValue *lvalue) {
    exprValue *primaryValueVal;

    // TODO
    if (lvalue->valType == varExpr_T) {
        Symbol *symbol = lvalue->symbolVal;
        if (symbol->scope == 0 ||
            symbol->type == USER_FUNC ||
            symbol->type == LIB_FUNC ||
            funcDepth == symbol->funcDepth) {

            primaryValueVal = emit_iftableitem(lvalue);
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

exprValue *Manage_primary_LPfuncdefRP(Function *funcdef) {
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
    exprValue *newStructVal;
    unsigned int &scope = scopeLevel;

    auto symbol = symbolTableObj.lookup_scope(id, scope);

    if (symbol == nullptr) {
        if (!isLibFunction(id)) {
            symbol = new Variable(id, scope, yylineno, funcDepth, currScopespace(), currScopespaceOffset());
            symbolTableObj.insert(id, symbol, scope);

            increaseCurrScopeOffset();

            newStructVal = lvalue_expr(symbol);
        } else {
            std::cerr << BRED "Variable \"" << id << "\" in line " << yylineno
                      << " attempts to shadow library function." RST << std::endl;

            newStructVal = new exprValue();
            newStructVal->valType = InvalidExpr_T;
        }
    } else {
        newStructVal = lvalue_expr(symbol);
    }

    assert((newStructVal->valType == InvalidExpr_T) || (newStructVal->valType == varExpr_T));

    return newStructVal;
}

exprValue *Manage_lvalue_globalid(std::string id) {
    exprValue *newStructVal;

    auto symbol = symbolTableObj.lookup_scope(id, 0);

    if (symbol == nullptr) {
        std::cerr << BRED "Undefined reference to global symbol \"" << id << "\" in line " << yylineno << "." RST << std::endl;

        newStructVal = new exprValue();
        newStructVal->valType = InvalidExpr_T;
    } else {
        newStructVal = lvalue_expr(symbol);
    }

    return newStructVal;
}

exprValue *Manage_lvalue_member(exprValue *member) {
    exprValue *lvalueValueVal;
    return lvalueValueVal;
}

/* Members */
exprValue *Manage_member_lvalueDOTid(exprValue *lvalue, std::string id) {
    return member_item(lvalue, id);
}

exprValue *Manage_member_lvalueLSBexprRSB(exprValue *lvalue, exprValue *expr) {
    exprValue *tableitem;

    lvalue = emit_iftableitem(lvalue);

    tableitem = new exprValue();
    tableitem->valType = TableitemExpr_T;
    tableitem->symbolVal = lvalue->symbolVal;

    tableitem->indexVal = expr;

    return tableitem;
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
exprValue *Manage_call_callLPelistRP(exprValue *call, exprValue *elist) {
    exprValue *callVal = make_call(call, elist);
    return callVal;
}

exprValue *Manage_call_lvaluecallsuffix(exprValue *lvalue, callValue *callsuffix) {
    exprValue *callVal;

    callVal->valType = varExpr_T;

    // TODO
    /*if (lvalue->valType == SymbolLvalue_T) {
        callVal->valType = lvalueCallSuffCall_T;
        callVal->callLvalueValue.lvalueVal = lvalue;
        callVal->callLvalueValue.callsuffixVal = callsuffix;
    }*/

    lvalue = emit_iftableitem(lvalue);
    if (callsuffix->method) {
        exprValue *t = lvalue;
        lvalue = emit_iftableitem(member_item(t, callsuffix->name));
        callsuffix->elist->next = t;
    }

    return make_call(lvalue, callsuffix->elist);
}

exprValue *Manage_call_LPfuncdefRPLPelistRP(Function *funcdef, exprValue *elist) {
    exprValue *func = new exprValue();
    func->valType = userfuncExpr_T;

    func->symbolVal = funcdef;

    return make_call(func, elist);
}

/* Call suffix */
callValue *Manage_callsuffix_normcall(callValue *normcall) {
    return normcall;
}

callValue *Manage_callsuffix_methodcall(callValue *methodcall) {
    return methodcall;
}

/* Normal call */
callValue *Manage_normcall_LPelistRP(exprValue *elist) {
    callValue *normcallVal = new callValue();

    normcallVal->elist = elist;
    normcallVal->method = 0;
    normcallVal->name = nullptr;

    return normcallVal;
}

/* Method call */
callValue *Manage_methodcall_DDOTidLPelistRP(std::string id, exprValue *elist) {
    callValue *methodcallVal = new callValue();

    methodcallVal->elist = elist;
    methodcallVal->method = true;
    methodcallVal->name = id;

    return methodcallVal;
}

/* elist */
exprValue *Manage_elist_exprOptRpt(exprOptRptValue *exprOptRpt) {
    exprValue *newStructVal;
    return newStructVal;
}

exprValue *Manage_elist() {
    exprValue *newStructVal;
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
exprValue *Manage_objectdef_LSBelistRSB(exprValue *elist) {
    exprValue *objdefVal = new exprValue();
    objdefVal->valType = newtableExpr_T;

    objdefVal->symbolVal = newTempvar();
    emit(table_create_iop, objdefVal, NULL, NULL);

    for (int i = 0; elist; elist = elist->next) {
        exprValue *constVal = new exprValue();
        constVal->valType = constnumExpr_T;
        constVal->numConstval = i++;

        emit(table_setelem_iop, objdefVal, constVal, elist);
    }

    return objdefVal;
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
    Function *newFunc = new Function(funcName, scopeLevel, yylineno, funcDepth, USER_FUNC, currScopespaceOffset(), nextQuadLabel());

    if (isLibFunction(funcName)) {
        std::cerr << BRED "Cannot define function \"" << funcName << "\" in line " << yylineno
                  << ". It would shadow a library function." RST << std::endl;

        delete newFunc;
        return nullptr;
    }

    auto symbol_in_table = symbolTableObj.lookup_scope(funcName, scopeLevel);

    if (symbol_in_table != nullptr) {
        std::cerr << BRED "Cannot define function \"" << funcName
                  << "\" in line " << yylineno << ". It shadows previous "
                  << type_names[symbol_in_table->type] << " defined in line "
                  << symbol_in_table->line << "." RST << std::endl;

        delete newFunc;
        return nullptr;
    } else {
        symbolTableObj.insert(funcName, newFunc, scopeLevel);
    }

    exprValue *funcprefix = new exprValue();
    funcprefix->valType = userfuncExpr_T;
    funcprefix->symbolVal = newFunc;

    emit(funcstart_iop, funcprefix, nullptr, nullptr);

    scopeOffsetStack.push(currScopespaceOffset());
    enterScopespace();
    resetFormalArgOffset();

    return newFunc;
}

unsigned long Manage_funcbody() {
    unsigned long scopeOffset = currScopespaceOffset();
    exitScopespace();

    return scopeOffset;
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
    enterScopespace();

    if (check_funcargs(idlist)) {
        while (idlist_ptr->valType == idlistIdIdlist_T) {
            Symbol *newArg = new Variable(idlist_ptr->value.idlistIdValue.idVal, scopeLevel, yylineno, funcDepth, currScopespace(), currScopespaceOffset());

            symbolTableObj.insert(newArg->name, newArg, scopeLevel);

            idlist_ptr = idlist_ptr->value.idlistIdValue.idlistVal;
        }

        if (idlist_ptr->valType == idIdlist_T) {
            Symbol *newArg = new Variable(idlist_ptr->value.id, scopeLevel, yylineno, funcDepth, currScopespace(), currScopespaceOffset());

            symbolTableObj.insert(newArg->name, newArg, scopeLevel);
        }
    }

    resetFunctionLocalOffset();
    --scopeLevel;
}

Function *Manage_funcdef(idlistValue *idlist, blockValue *block) {
    static unsigned long long unnamed_function_counter = 0;

    std::string function_name = std::string("$f") + std::to_string(unnamed_function_counter);

    return nullptr;
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
forstmtValue *Manage_for(exprValue *elistFirst, exprValue *expr, exprValue *elistLast, stmtValue *stmt) {
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