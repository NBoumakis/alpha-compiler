#include "../include/rules.h"

programValue Manage_program(stmtListValue stmtList) {
    struct programValue newStructVal;
    return newStructVal;
}

stmtListValue Manage_stmtList_stmt(stmtListValue stmtList, stmtValue stmt) {
    struct stmtListValue stmtListVal;
    return stmtListVal;
}

stmtListValue Manage_stmtList() {
    struct stmtListValue stmtListVal;
    return stmtListVal;
}

/* Statements */
stmtValue Manage_stmt_expr(exprValue expr) {
    struct stmtValue stmtValueVal;
    return stmtValueVal;
}

stmtValue Manage_stmt_ifstmt(ifstmtValue ifstmt) {
    struct stmtValue stmtValueVal;
    return stmtValueVal;
}

stmtValue Manage_stmt_whilestmt(whilestmtValue whilestmt) {
    struct stmtValue stmtValueVal;
    return stmtValueVal;
}

stmtValue Manage_stmt_forstmt(forstmtValue forstmt) {
    struct stmtValue stmtValueVal;
    return stmtValueVal;
}

stmtValue Manage_stmt_returnstmt(returnstmtValue returnstmt) {
    struct stmtValue stmtValueVal;
    return stmtValueVal;
}

stmtValue Manage_stmt_break() {
    struct stmtValue stmtValueVal;
    return stmtValueVal;
}

stmtValue Manage_stmt_continue() {
    struct stmtValue stmtValueVal;
    return stmtValueVal;
}

stmtValue Manage_stmt_block(blockValue block) {
    struct stmtValue stmtValueVal;
    return stmtValueVal;
}

stmtValue Manage_stmt_funcdef(funcdefValue funcdef) {
    struct stmtValue stmtValueVal;
    return stmtValueVal;
}

stmtValue Manage_stmt_semicolon() {
    struct stmtValue stmtValueVal;
    return stmtValueVal;
}

/* Expressions */
exprValue Manage_expr_assignexpr(assignexprValue assignexpr) {
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_PLUS_expr(exprValue exprLeft, exprValue exprRight) {
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_MINUS_expr(exprValue exprLeft, exprValue exprRight) {
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_MUL_expr(exprValue exprLeft, exprValue exprRight) {
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_DIV_expr(exprValue exprLeft, exprValue exprRight) {
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_MOD_expr(exprValue exprLeft, exprValue exprRight) {
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_GT_expr(exprValue exprLeft, exprValue exprRight) {
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_GE_expr(exprValue exprLeft, exprValue exprRight) {
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_LT_expr(exprValue exprLeft, exprValue exprRight) {
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_LE_expr(exprValue exprLeft, exprValue exprRight) {
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_EQUAL_expr(exprValue exprLeft, exprValue exprRight) {
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_NEQUAL_expr(exprValue exprLeft, exprValue exprRight) {
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_AND_expr(exprValue exprLeft, exprValue exprRight) {
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_OR_expr(exprValue exprLeft, exprValue exprRight) {
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_term(termValue term) {
    struct exprValue exprValueVal;
    return exprValueVal;
}

/* Terms */
termValue Manage_term_LPexprRP(exprValue expr) {
    struct termValue termValueVal;
    return termValueVal;
}

termValue Manage_term_notexpr(exprValue expr) {
    struct termValue termValueVal;
    return termValueVal;
}

termValue Manage_term_PPlval(lvalueValue lvalue) {
    struct termValue termValueVal;
    return termValueVal;
}

termValue Manage_term_lvaluePP(lvalueValue lvalue) {
    struct termValue termValueVal;
    return termValueVal;
}

termValue Manage_term_MMlval(lvalueValue lvalue) {
    struct termValue termValueVal;
    return termValueVal;
}

termValue Manage_term_lvalueMM(lvalueValue lvalue) {
    struct termValue termValueVal;
    return termValueVal;
}

termValue Manage_term_primary(primaryValue primary) {
    struct termValue termValueVal;
    return termValueVal;
}

termValue Manage_term_minusexpr(exprValue expr) {
    struct termValue termValueVal;
    return termValueVal;
}

/* Assign expression */
assignexprValue Manage_assignexpr_lvalueASSIGNexpr(lvalueValue lvalue, exprValue expr) {
    /*  1)an lvalue einai function -> error
        2) switch gia to lvalue
            -an einai id call  Manage_lvalue_id
            -an einai local_id call Manage_lvalue_localid
            -an eina namescapse_id  Manage_lvalue_globalid*/
}

/* Primary */
primaryValue Manage_primary_lvalue(lvalueValue lvalue) {
    struct primaryValue primaryValueVal;
    return primaryValueVal;
}

primaryValue Manage_primary_call(callValue call) {
    struct primaryValue primaryValueVal;
    return primaryValueVal;
}

primaryValue Manage_primary_objectdef(objectdefValue objdef) {
    struct primaryValue primaryValueVal;
    return primaryValueVal;
}

primaryValue Manage_primary_LPfuncdefRP(funcdefValue funcdef) {
    struct primaryValue primaryValueVal;
    return primaryValueVal;
}

primaryValue Manage_primary_const(constValue constVal) {
    struct primaryValue primaryValueVal;
    return primaryValueVal;
}

/* lvalue */
lvalueValue Manage_lvalue_id(idValue id) {
    /*(front3 slide20)*/
}

lvalueValue Manage_lvalue_localid(idValue id) {
    /*  1)lookup_sympol
        2)conflict me library funtion
        3)lookup_scope
        4)conflict me function sto idio scope(front 3 slide 11)
        5)an den yparxei sto scope insert ston symbol table
        6)an to scope=0 ignore local (front3 slide 19)*/
}

lvalueValue Manage_lvalue_globalid(idValue id) {
    /*  1)yparxei metablhth me ayto to onoma
        sto scope=0?*/
}

lvalueValue Manage_lvalue_member(memberValue member) {
    struct lvalueValue lvalueValueVal;
    return lvalueValueVal;
}

/* Members */
memberValue Manage_member_lvalueDOTid(lvalueValue lvalue, idValue id) {
    struct memberValue memberVal;
    return memberVal;
}

memberValue Manage_member_lvalueLSBexprRSB(lvalueValue lvalue, exprValue expr) {
    struct memberValue memberVal;
    return memberVal;
}

memberValue Manage_member_callDOTid(callValue call, idValue id) {
    struct memberValue memberVal;
    return memberVal;
}

memberValue Manage_member_callLSBexprRSB(callValue call, exprValue expr) {
    struct memberValue memberVal;
    return memberVal;
}

/* Calls */
callValue Manage_call_callLPelistRP(callValue call, elistValue elist) {
    struct callValue callVal;
    return callVal;
}

callValue Manage_call_lvaluecallsuffix(lvalueValue lvalue, callsuffixValue callsuffix) {
    struct callValue callVal;
    return callVal;
}

callValue Manage_call_LPfuncdefRPLPelistRP(funcdefValue funcdef, elistValue elist) {
    struct callValue callVal;
    return callVal;
}

/* Call suffix */
callsuffixValue Manage_callsuffix_normcall(normcallValue normcall);

callsuffixValue Manage_callsuffix_methodcall(methodcallValue methodcall);

/* Normal call */
normcallValue Manage_normcall_LPelistRP(elistValue elist);

/* Method call */
methodcallValue Manage_methodcall_DDOTidLPelistRP(idValue id, elistValue elist);

/* elist */
elistValue Manage_elist_exprOptRpt(exprOptRptValue exprOptRpt);

elistValue Manage_elist();

/* Expression optional and repeatable */
exprOptRptValue Manage_exprOR_exprOR(exprValue expr, exprOptRptValue exprOptRpt);

exprOptRptValue Manage_exprOR_expr(exprValue expr);

/* Objectdef */
objectdefValue Manage_objectdef_LSBelistRSB(elistValue elist);

objectdefValue Manage_objectdef_LSBindexedRSB(indexedValue indexed);

/* Indexed */
indexedValue Manage_indexed(indelemlistValue indelemlist);

/* Indexed element list */
indelemlistValue Manage_indelemlist(indexedelemValue indexedelem, indelemlistValue indelemlist);

indelemlistValue Manage_indelemlist_indexedelem(indexedelemValue indexedelem);

indexedelemValue Manage_indexedelem_LCB_expr_COLON_expr_RCB(exprValue key, exprValue value);

/* Block */
blockValue Manage_block_LCBstmtRCB(stmtValue stmt) {
    /*  1){ scope++
        2)hide(scope);scope--}*/
}

/* Funcdef */
funcdefValue Manage_funcdef_id(idValue id, idlistValue idlist, blockValue block) {
    /*  1)( ++scope
        2)} hide(scope) ;scope--
        3)conflict me library function
        4)lookup_symbol,no:insert
        5)yes:lookup_scope
        6)conflict me function sto idio scope/variable ( front3 slide 11)
        */
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
}

/* Constants */
constValue Manage_const_int(int intVal);

constValue Manage_const_real(double doubleVal);

constValue Manage_const_string(std::string strVal);

constValue Manage_const_nil();

constValue Manage_const_true();

constValue Manage_const_false();

/* ID list */
idlistValue Manage_idlist_ID(idValue id);

idlistValue Manage_idlist_idlist_comma_id(idlistValue idlist, idValue id);

idlistValue Manage_idlist();

/* If statement */
ifstmtValue Manage_ifstmt(exprValue expr, stmtValue stmt, elseValue elseVal);

/* else */
elseValue Manage_else_stmt(stmtValue stmt);

elseValue Manage_else();

/* While statement */
whilestmtValue Manage_whilestmt(exprValue expr, stmtValue stmt);

/* For statement */
forstmtValue Manage_for(elistValue elist, exprValue expr, elistValue elist, stmtValue stmt);

/* Return statement */
returnstmtValue Manage_returnstmt(retValue ret);

/* Return */
retValue Manage_ret_expr(exprValue expr);

retValue Manage_ret();