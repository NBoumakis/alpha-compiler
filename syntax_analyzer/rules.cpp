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
    struct assignexprValue assignexprValueVal;
    return assignexprValueVal;
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
    struct lvalueValue lvalueValueVal;
    return lvalueValueVal;
}

lvalueValue Manage_lvalue_localid(idValue){
    struct lvalueValue lvalueValueVal;
    return lvalueValueVal;
}

lvalueValue Manage_lvalue_globalid(idValue){
    struct lvalueValue lvalueValueVal;
    return lvalueValueVal;
}

lvalueValue Manage_lvalue_member(memberValue){
    struct lvalueValue lvalueValueVal;
    return lvalueValueVal;
}