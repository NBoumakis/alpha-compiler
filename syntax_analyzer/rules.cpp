#include "rules.h"
#include "symbol_table.h"
#include <iostream>

programValue Manage_program(stmtListValue stmtList) {
    programValue newStructVal;
    return newStructVal;
}

stmtListValue Manage_stmtList_stmt(stmtListValue stmtList, stmtValue stmt) {
    stmtListValue stmtListVal;
    return stmtListVal;
}

stmtListValue Manage_stmtList() {
    stmtListValue stmtListVal;
    return stmtListVal;
}

/* Statements */
stmtValue Manage_stmt_expr(exprValue expr) {
    stmtValue stmtValueVal;
    return stmtValueVal;
}

stmtValue Manage_stmt_ifstmt(ifstmtValue ifstmt) {
    stmtValue stmtValueVal;
    return stmtValueVal;
}

stmtValue Manage_stmt_whilestmt(whilestmtValue whilestmt) {
    stmtValue stmtValueVal;
    return stmtValueVal;
}

stmtValue Manage_stmt_forstmt(forstmtValue forstmt) {
    stmtValue stmtValueVal;
    return stmtValueVal;
}

stmtValue Manage_stmt_returnstmt(returnstmtValue returnstmt) {
    stmtValue stmtValueVal;
    return stmtValueVal;
}

stmtValue Manage_stmt_break() {
    stmtValue stmtValueVal;
    return stmtValueVal;
}

stmtValue Manage_stmt_continue() {
    stmtValue stmtValueVal;
    return stmtValueVal;
}

stmtValue Manage_stmt_block(blockValue block) {
    stmtValue stmtValueVal;
    return stmtValueVal;
}

stmtValue Manage_stmt_funcdef(funcdefValue funcdef) {
    stmtValue stmtValueVal;
    return stmtValueVal;
}

stmtValue Manage_stmt_semicolon() {
    stmtValue stmtValueVal;
    return stmtValueVal;
}

/* Expressions */
exprValue Manage_expr_assignexpr(assignexprValue assignexpr) {
    exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_PLUS_expr(exprValue exprLeft, exprValue exprRight) {
    exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_MINUS_expr(exprValue exprLeft, exprValue exprRight) {
    exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_MUL_expr(exprValue exprLeft, exprValue exprRight) {
    exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_DIV_expr(exprValue exprLeft, exprValue exprRight) {
    exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_MOD_expr(exprValue exprLeft, exprValue exprRight) {
    exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_GT_expr(exprValue exprLeft, exprValue exprRight) {
    exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_GE_expr(exprValue exprLeft, exprValue exprRight) {
    exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_LT_expr(exprValue exprLeft, exprValue exprRight) {
    exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_LE_expr(exprValue exprLeft, exprValue exprRight) {
    exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_EQUAL_expr(exprValue exprLeft, exprValue exprRight) {
    exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_NEQUAL_expr(exprValue exprLeft, exprValue exprRight) {
    exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_AND_expr(exprValue exprLeft, exprValue exprRight) {
    exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_OR_expr(exprValue exprLeft, exprValue exprRight) {
    exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_term(termValue term) {
    exprValue exprValueVal;
    return exprValueVal;
}

/* Terms */
termValue Manage_term_LPexprRP(exprValue expr) {
    termValue termValueVal;
    return termValueVal;
}

termValue Manage_term_notexpr(exprValue expr) {
    termValue termValueVal;
    return termValueVal;
}

termValue Manage_term_PPlval(lvalueValue lvalue) {
    termValue termValueVal;
    return termValueVal;
}

termValue Manage_term_lvaluePP(lvalueValue lvalue) {
    termValue termValueVal;
    return termValueVal;
}

termValue Manage_term_MMlval(lvalueValue lvalue) {
    termValue termValueVal;
    return termValueVal;
}

termValue Manage_term_lvalueMM(lvalueValue lvalue) {
    termValue termValueVal;
    return termValueVal;
}

termValue Manage_term_primary(primaryValue primary) {
    termValue termValueVal;
    return termValueVal;
}

termValue Manage_term_minusexpr(exprValue expr) {
    termValue termValueVal;
    return termValueVal;
}

/* Assign expression */
assignexprValue Manage_assignexpr_lvalueASSIGNexpr(lvalueValue lvalue, exprValue expr) {
    /*  1)an lvalue einai function -> error
        2) switch gia to lvalue
            -an einai id call  Manage_lvalue_id
            -an einai local_id call Manage_lvalue_localid
            -an eina namescapse_id  Manage_lvalue_globalid*/
    assignexprValue newStructVal;
    return newStructVal;
}

/* Primary */
primaryValue Manage_primary_lvalue(lvalueValue lvalue) {
    primaryValue primaryValueVal;
    return primaryValueVal;
}

primaryValue Manage_primary_call(callValue call) {
    primaryValue primaryValueVal;
    return primaryValueVal;
}

primaryValue Manage_primary_objectdef(objectdefValue objdef) {
    primaryValue primaryValueVal;
    return primaryValueVal;
}

primaryValue Manage_primary_LPfuncdefRP(funcdefValue funcdef) {
    primaryValue primaryValueVal;
    return primaryValueVal;
}

primaryValue Manage_primary_const(constValue constVal) {
    primaryValue primaryValueVal;
    return primaryValueVal;
}

/* lvalue */
lvalueValue Manage_lvalue_id(std::string id) {
    /*(front3 slide20)*/
    lvalueValue newStructVal;
    return newStructVal;
}

lvalueValue Manage_lvalue_localid(std::string id) {
    /*  1)lookup_sympol
        2)conflict me library funtion
        3)lookup_scope
        4)conflict me function sto idio scope(front 3 slide 11)
        5)an den yparxei sto scope insert ston symbol table
        6)an to scope=0 ignore local (front3 slide 19)*/
    lvalueValue newStructVal;
    return newStructVal;
}

lvalueValue Manage_lvalue_globalid(std::string id) {
    /*  1)yparxei metablhth me ayto to onoma
        sto scope=0?*/
    lvalueValue newStructVal;
    return newStructVal;
}

lvalueValue Manage_lvalue_member(memberValue member) {
    lvalueValue lvalueValueVal;
    return lvalueValueVal;
}

/* Members */
memberValue Manage_member_lvalueDOTid(lvalueValue lvalue, std::string id) {
    memberValue memberVal;
    return memberVal;
}

memberValue Manage_member_lvalueLSBexprRSB(lvalueValue lvalue, exprValue expr) {
    memberValue memberVal;
    return memberVal;
}

memberValue Manage_member_callDOTid(callValue call, std::string id) {
    memberValue memberVal;
    return memberVal;
}

memberValue Manage_member_callLSBexprRSB(callValue call, exprValue expr) {
    memberValue memberVal;
    return memberVal;
}

/* Calls */
callValue Manage_call_callLPelistRP(callValue call, elistValue elist) {
    callValue callVal;
    return callVal;
}

callValue Manage_call_lvaluecallsuffix(lvalueValue lvalue, callsuffixValue callsuffix) {
    callValue callVal;
    return callVal;
}

callValue Manage_call_LPfuncdefRPLPelistRP(funcdefValue funcdef, elistValue elist) {
    callValue callVal;
    return callVal;
}

/* Call suffix */
callsuffixValue Manage_callsuffix_normcall(normcallValue normcall) {
    callsuffixValue newStructVal;
    return newStructVal;
}

callsuffixValue Manage_callsuffix_methodcall(methodcallValue methodcall) {
    callsuffixValue newStructVal;
    return newStructVal;
}

/* Normal call */
normcallValue Manage_normcall_LPelistRP(elistValue elist) {
    normcallValue newStructVal;
    return newStructVal;
}

/* Method call */
methodcallValue Manage_methodcall_DDOTidLPelistRP(std::string id, elistValue elist) {
    methodcallValue newStructVal;
    return newStructVal;
}

/* elist */
elistValue Manage_elist_exprOptRpt(exprOptRptValue exprOptRpt) {
    elistValue newStructVal;
    return newStructVal;
}

elistValue Manage_elist() {
    elistValue newStructVal;
    return newStructVal;
}

/* Expression optional and repeatable */
exprOptRptValue Manage_exprOR_exprOR(exprValue expr, exprOptRptValue exprOptRpt) {
    exprOptRptValue newStructVal;
    return newStructVal;
}

exprOptRptValue Manage_exprOR_expr(exprValue expr) {
    exprOptRptValue newStructVal;
    return newStructVal;
}

/* Objectdef */
objectdefValue Manage_objectdef_LSBelistRSB(elistValue elist) {
    objectdefValue newStructVal;
    return newStructVal;
}

objectdefValue Manage_objectdef_LSBindexedRSB(indexedValue indexed) {
    objectdefValue newStructVal;
    return newStructVal;
}

/* Indexed */
indexedValue Manage_indexed(indelemlistValue indelemlist) {
    indexedValue newStructVal;
    return newStructVal;
}

/* Indexed element list */
indelemlistValue Manage_indelemlist(indexedelemValue indexedelem, indelemlistValue indelemlist) {
    indelemlistValue newStructVal;
    return newStructVal;
}

indelemlistValue Manage_indelemlist_indexedelem(indexedelemValue indexedelem) {
    indelemlistValue newStructVal;
    return newStructVal;
}

indexedelemValue Manage_indexedelem_LCB_expr_COLON_expr_RCB(exprValue key, exprValue value) {
    indexedelemValue newStructVal;
    return newStructVal;
}

/* Block */
blockValue Manage_block_LCBstmtRCB(stmtListValue stmt) {
    /*  1){ scope++
        2)hide(scope);scope--}*/
    blockValue newStructVal;
    return newStructVal;
}

/* Funcdef */
funcdefValue Manage_funcdef_id(std::string id, idlistValue idlist, blockValue block) {
    funcdefValue fval;
    /*  1)(
        2)} hide(scope) ;scope--
        3)conflict me library function
        4)lookup_symbol,no:insert
        5)yes:lookup_scope
        6)conflict me function sto idio scope/variable ( front3 slide 11)
        */

    unsigned int &scope = scopeLevel;

    std::cout << scope << std::endl;

    if (isLibFunction(id)) {
        std::cerr << "Cannot define function " << id << ". It conflicts with library function." << std::endl;

        fval.valType = InvalidFuncdef_T;
        return fval;
    }

    auto symbol_in_table = symbolTableObj.lookup_scope(id, scope);

    if (symbol_in_table != nullptr) {
        std::cerr << "Cannot define function " << id << ". It conflicts with ";

        switch (symbol_in_table->type) {
        case USER_FUNC:
            std::cerr << "previous user function";
            break;

        case LOCAL_VAR:
            std::cerr << "local variable";
            break;

        case GLOBAL_VAR:
            std::cerr << "global variable";
            break;

        case FORMAL_ARG:
            std::cerr << "formal argument";
            break;

        default:
            std::cerr << "This shouldn't have happened";

            break;
        }

        std::cerr << " last defined in line " << symbol_in_table->line << "." << std::endl;

        fval.valType = InvalidFuncdef_T;
        return fval;
    }

    return fval;
}

funcdefValue Manage_funcdef(idlistValue idlist, blockValue block) {
    /*(front3 slide 22)
      1)( ++scope
        2)}hide(scope) scope--
        3)diko mas onoma
        3)conflict me library function
        4)lookup_symbol,no:insert
        5)yes:lookup_scope
        6)conflict me function sto idio scope/variable ( front3 slide 11)
        */
    funcdefValue newStructVal;
    return newStructVal;
}

/* Constants */
constValue Manage_const_int(int intVal) {
    constValue newStructVal;
    return newStructVal;
}

constValue Manage_const_real(double doubleVal) {
    constValue newStructVal;
    return newStructVal;
}

constValue Manage_const_string(std::string strVal) {
    constValue newStructVal;
    return newStructVal;
}

constValue Manage_const_nil() {
    constValue newStructVal;
    return newStructVal;
}

constValue Manage_const_true() {
    constValue newStructVal;
    return newStructVal;
}

constValue Manage_const_false() {
    constValue newStructVal;
    return newStructVal;
}

/* ID list */
idlistValue Manage_idlist_ID(std::string id) {
    idlistValue newStructVal;
    return newStructVal;
}

idlistValue Manage_idlist_idlist_comma_id(idlistValue idlist, std::string id) {
    idlistValue newStructVal;
    return newStructVal;
}

idlistValue Manage_idlist() {
    idlistValue newStructVal;
    return newStructVal;
}

/* If statement */
ifstmtValue Manage_ifstmt(exprValue expr, stmtValue stmt, elseValue elseVal) {
    ifstmtValue newStructVal;
    return newStructVal;
}

/* else */
elseValue Manage_else_stmt(stmtValue stmt) {
    elseValue newStructVal;
    return newStructVal;
}

elseValue Manage_else() {
    elseValue newStructVal;
    return newStructVal;
}

/* While statement */
whilestmtValue Manage_whilestmt(exprValue expr, stmtValue stmt) {
    whilestmtValue newStructVal;
    return newStructVal;
}

/* For statement */
forstmtValue Manage_for(elistValue elistFirst, exprValue expr, elistValue elistLast, stmtValue stmt) {
    forstmtValue newStructVal;
    return newStructVal;
}

/* Return statement */
returnstmtValue Manage_returnstmt(retValue ret) {
    returnstmtValue newStructVal;
    return newStructVal;
}

/* Return */
retValue Manage_ret_expr(exprValue expr) {
    retValue newStructVal;
    return newStructVal;
}

retValue Manage_ret() {
    retValue newStructVal;
    return newStructVal;
}