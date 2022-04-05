#include "../include/rules.h"

programValue Manage_program(stmtListValue){
    struct programValue newStructVal;
    return newStructVal;
}

stmtListValue Manage_stmtList_stmt(stmtListValue, stmtValue){
    struct stmtListValue stmtListVal;
    return stmtListVal;
}

stmtListValue Manage_stmtList(){
    struct stmtListValue stmtListVal;
    return stmtListVal;
}

/* Statements */
stmtValue Manage_stmt_expr(exprValue){
    struct stmtValue stmtValueVal;
    return stmtValueVal;
}

stmtValue Manage_stmt_ifstmt(ifstmtValue){
    struct stmtValue stmtValueVal;
    return stmtValueVal;
}

stmtValue Manage_stmt_whilestmt(whilestmtValue){
    struct stmtValue stmtValueVal;
    return stmtValueVal;
}

stmtValue Manage_stmt_forstmt(forstmtValue){
    struct stmtValue stmtValueVal;
    return stmtValueVal;
}

stmtValue Manage_stmt_returnstmt(returnstmtValue){
    struct stmtValue stmtValueVal;
    return stmtValueVal;
}

stmtValue Manage_stmt_break(){
    struct stmtValue stmtValueVal;
    return stmtValueVal;
}

stmtValue Manage_stmt_continue(){
    struct stmtValue stmtValueVal;
    return stmtValueVal;
}

stmtValue Manage_stmt_block(blockValue){
    struct stmtValue stmtValueVal;
    return stmtValueVal;
}

stmtValue Manage_stmt_funcdef(funcdefValue){
    struct stmtValue stmtValueVal;
    return stmtValueVal;
}

stmtValue Manage_stmt_semicolon(){
    struct stmtValue stmtValueVal;
    return stmtValueVal;
}

/* Expressions */
exprValue Manage_expr_assignexpr(assignexprValue){
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_PLUS_expr(exprValue, exprValue){
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_MINUS_expr(exprValue, exprValue){
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_MUL_expr(exprValue, exprValue){
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_DIV_expr(exprValue, exprValue){
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_MOD_expr(exprValue, exprValue){
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_GT_expr(exprValue, exprValue){
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_GE_expr(exprValue, exprValue){
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_LT_expr(exprValue, exprValue){
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_LE_expr(exprValue, exprValue){
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_EQUAL_expr(exprValue, exprValue){
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_NEQUAL_expr(exprValue, exprValue){
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_AND_expr(exprValue, exprValue){
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_expr_OR_expr(exprValue, exprValue){
    struct exprValue exprValueVal;
    return exprValueVal;
}

exprValue Manage_expr_term(termValue){
    struct exprValue exprValueVal;
    return exprValueVal;
}

/* Terms */
termValue Manage_term_LPexprRP(exprValue){
    struct termValue termValueVal;
    return termValueVal;
}

termValue Manage_term_notexpr(exprValue){
    struct termValue termValueVal;
    return termValueVal;
}

termValue Manage_term_PPlval(lvalueValue){
    struct termValue termValueVal;
    return termValueVal;
}

termValue Manage_term_lvaluePP(lvalueValue){
    struct termValue termValueVal;
    return termValueVal;
}

termValue Manage_term_MMlval(lvalueValue){
    struct termValue termValueVal;
    return termValueVal;
}

termValue Manage_term_lvalueMM(lvalueValue){
    struct termValue termValueVal;
    return termValueVal;
}

termValue Manage_term_primary(primaryValue){
    struct termValue termValueVal;
    return termValueVal;
}

termValue Manage_term_minusexpr(exprValue){
    struct termValue termValueVal;
    return termValueVal;
}

/* Assign expression */
assignexprValue Manage_assignexpr_lvalueASSIGNexpr(lvalueValue, exprValue){
    /*  1)an lvalue einai function -> error
        2) switch gia to lvalue
            -an einai id call  Manage_lvalue_id
            -an einai local_id call Manage_lvalue_localid
            -an eina namescapse_id  Manage_lvalue_globalid*/
}

/* Primary */
primaryValue Manage_primary_lvalue(lvalueValue){
    struct primaryValue primaryValueVal;
    return primaryValueVal;
}

primaryValue Manage_primary_call(callValue){
    struct primaryValue primaryValueVal;
    return primaryValueVal;
}

primaryValue Manage_primary_objectdef(objectdefValue){
    struct primaryValue primaryValueVal;
    return primaryValueVal;
}

primaryValue Manage_primary_LPfuncdefRP(funcdefValue){
    struct primaryValue primaryValueVal;
    return primaryValueVal;
}

primaryValue Manage_primary_const(constValue){
    struct primaryValue primaryValueVal;
    return primaryValueVal;
}

/* lvalue */
lvalueValue Manage_lvalue_id(idValue){
    /*(front3 slide20)*/
}

lvalueValue Manage_lvalue_localid(idValue){
    /*  1)lookup_sympol
        2)conflict me library funtion
        3)lookup_scope 
        4)conflict me function sto idio scope(front 3 slide 11)
        5)an den yparxei sto scope insert ston symbol table
        6)an to scope=0 ignore local (front3 slide 19)*/
}

lvalueValue Manage_lvalue_globalid(idValue){
    /*  1)yparxei metablhth me ayto to onoma
        sto scope=0?*/
}

lvalueValue Manage_lvalue_member(memberValue){
    struct lvalueValue lvalueValueVal;
    return lvalueValueVal;
}

/* Members */
memberValue Manage_member_lvalueDOTid(lvalueValue, idValue){
    struct memberValue memberVal;
    return memberVal;
}

memberValue Manage_member_lvalueLSBexprRSB(lvalueValue, exprValue){
    struct memberValue memberVal;
    return memberVal;
}

memberValue Manage_member_callDOTid(callValue, idValue){
    struct memberValue memberVal;
    return memberVal;
}

memberValue Manage_member_callLSBexprRSB(callValue, exprValue){
    struct memberValue memberVal;
    return memberVal;
}

/* Calls */
callValue Manage_call_callLPelistRP(callValue, elistValue){
    struct callValue callVal;
    return callVal;
}

callValue Manage_call_lvaluecallsuffix(lvalueValue, callsuffixValue){
    struct callValue callVal;
    return callVal;
}

callValue Manage_call_LPfuncdefRPLPelistRP(funcdefValue, elistValue){
    struct callValue callVal;
    return callVal;
}

/* Call suffix */
callsuffixValue Manage_callsuffix_normcall(normcallValue);

callsuffixValue Manage_callsuffix_methodcall(methodcallValue);

/* Normal call */
normcallValue Manage_normcall_LPelistRP(elistValue);

/* Method call */
methodcallValue Manage_methodcall_DDOTidLPelistRP(idValue, elistValue);

/* elist */
elistValue Manage_elist_exprOptRpt(exprOptRptValue);

elistValue Manage_elist();

/* Expression optional and repeatable */
exprOptRptValue Manage_exprOR_exprOR(exprValue, exprOptRptValue);

exprOptRptValue Manage_exprOR_expr(exprValue);

/* Objectdef */
objectdefValue Manage_objectdef_LSBelistRSB(elistValue);

objectdefValue Manage_objectdef_LSBindexedRSB(indexedValue);

/* Indexed */
indexedValue Manage_indexed(indelemlistValue);

/* Indexed element list */
indelemlistValue Manage_indelemlist(indexedelemValue, indelemlistValue);

indelemlistValue Manage_indelemlist_indexedelem(indexedelemValue);

indexedelemValue Manage_indexedelem_LCB_expr_COLON_expr_RCB(exprValue, exprValue);

/* Block */
blockValue Manage_block_LCBstmtRCB(stmtValue){
    /*  1){ scope++
        2)hide(scope);scope--}*/
}

/* Funcdef */
funcdefValue Manage_funcdef_id(idValue, idlistValue, blockValue){
    /*  1)( ++scope
        2)} hide(scope) ;scope--
        3)conflict me library function
        4)lookup_symbol,no:insert
        5)yes:lookup_scope
        6)conflict me function sto idio scope/variable ( front3 slide 11)
        */
}

funcdefValue Manage_funcdef(idlistValue, blockValue){
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
constValue Manage_const_int(int);

constValue Manage_const_real(double);

constValue Manage_const_string(std::string);

constValue Manage_const_nil();

constValue Manage_const_true();

constValue Manage_const_false();

/* ID list */
idlistValue Manage_idlist_ID(idValue);

idlistValue Manage_idlist_idlist_comma_id(idlistValue, idValue);

idlistValue Manage_idlist();

/* If statement */
ifstmtValue Manage_ifstmt(exprValue, stmtValue, elseValue);

/* else */
elseValue Manage_else_stmt(stmtValue);

elseValue Manage_else();

/* While statement */
whilestmtValue Manage_whilestmt(exprValue, stmtValue);

/* For statement */
forstmtValue Manage_for(elistValue, exprValue, elistValue, stmtValue);

/* Return statement */
returnstmtValue Manage_returnstmt(retValue);

/* Return */
retValue Manage_ret_expr(exprValue);

retValue Manage_ret();