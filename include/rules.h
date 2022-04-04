#ifndef __RULES_H
#define __RULES_H

#include "../include/types.h"

/* Program */
programValue Manage_program(stmtListValue);

/* Statement list */
stmtListValue Manage_stmtList_stmt(stmtListValue, stmtValue);

/* Statements */
stmtValue Manage_stmt_expr(exprValue);

stmtValue Manage_stmt_ifstmt(ifstmtValue);

stmtValue Manage_stmt_whilestmt(whilestmtValue);

stmtValue Manage_stmt_forstmt(forstmtValue);

stmtValue Manage_stmt_returnstmt(returnstmtValue);

stmtValue Manage_stmt_break();

stmtValue Manage_stmt_continue();

stmtValue Manage_stmt_block(blockstmtValue);

stmtValue Manage_stmt_funcdef(funcdefValue);

/* Expressions */
exprValue Manage_expr_assignexpr(assignexprValue);

exprValue Manage_expr_expr_PLUS_expr(exprValue, exprValue);

exprValue Manage_expr_expr_MINUS_expr(exprValue, exprValue);

exprValue Manage_expr_expr_MUL_expr(exprValue, exprValue);

exprValue Manage_expr_expr_DIV_expr(exprValue, exprValue);

exprValue Manage_expr_expr_MOD_expr(exprValue, exprValue);

exprValue Manage_expr_expr_GT_expr(exprValue, exprValue);

exprValue Manage_expr_expr_GE_expr(exprValue, exprValue);

exprValue Manage_expr_expr_LT_expr(exprValue, exprValue);

exprValue Manage_expr_expr_LE_expr(exprValue, exprValue);

exprValue Manage_expr_expr_EQUAL_expr(exprValue, exprValue);

exprValue Manage_expr_expr_NEQUAL_expr(exprValue, exprValue);

exprValue Manage_expr_expr_AND_expr(exprValue, exprValue);

exprValue Manage_expr_expr_OR_expr(exprValue, exprValue);

exprValue Manage_expr_term(termValue);

/* Terms */
termValue Manage_term_LPexprRP(exprValue);

termValue Manage_term_notexpr(exprValue);

termValue Manage_term_PPlval(lvalueValue);

termValue Manage_term_lvaluePP(lvalueValue);

termValue Manage_term_MMlval(lvalueValue);

termValue Manage_term_lvalueMM(lvalueValue);

termValue Manage_term_primary(primaryValue);

termValue Manage_term_minusexpr(exprValue);

/* Assign expression */
assignexprValue Manage_assignexpr_lvalueASSIGNexpr(lvalueValue, exprValue);

/* Primary */
primaryValue Manage_primary_lvalue(lvalueValue);

primaryValue Manage_primary_call(callValue);

primaryValue Manage_primary_objectdef(objectdefValue);

primaryValue Manage_primary_LPfuncdefRP(funcdefValue);

primaryValue Manage_primary_const(constValue);

/* lvalue */
lvalueValue Manage_lvalue_id(idValue);

lvalueValue Manage_lvalue_localid(idValue);

lvalueValue Manage_lvalue_globalid(idValue);

lvalueValue Manage_lvalue_member(memberValue);

/* Members */
memberValue Manage_member_lvalueDOTid(lvalueValue, idValue);

memberValue Manage_member_lvalueLSBexprRSB(lvalueValue, exprValue);

memberValue Manage_member_callDOTid(callValue, idValue);

memberValue Manage_member_callLSBexprRSB(callValue, exprValue);

/* Calls */
callValue Manage_call_callLPelistRP(callValue, elistValue);

callValue Manage_call_lvaluecallsuffix(lvalueValue, callsuffixValue);

callValue Manage_call_LPfuncdefRPLPelistRP(funcdefValue, elistValue);

/* Call suffix */
callsuffixValue Manage_callsuffix_normcall(normcallValue);

callsuffixValue Manage_callsuffix_methodcall(methodcallValue);

/* Normal call */
normcallValue Manage_normcall_LPelistRP(elistValue);

/* Method call */
methodcallValue Manage_methodcall_DDOTidLPelistRP(idValue, elistValue);

/* elist */
elistValue Manage_elist_exprOptRpt(exprOptRptValue);

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
blockValue Manage_block_LCBstmtRCB(stmtValue);

/* Funcdef */
funcdefValue Manage_funcdef_id(idValue, idlistValue, blockValue);

funcdefValue Manage_funcdef(idlistValue, blockValue);

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

/* If statement */
ifstmtValue Manage_ifstmt(exprValue, stmtValue, elseValue);

/* else */
elseValue Manage_else(stmtValue);

/* While statement */
whilestmtValue Manage_whilestmt(exprValue, stmtValue);

/* For statement */
forstmtValue Manage_for(elistValue, exprValue, elistValue, stmtValue);

/* Return statement */
returnstmtValue Manage_returnstmt(retValue);

/* Return */
retValue Manage_ret_expr(exprValue);

#endif /* __RULES_H */