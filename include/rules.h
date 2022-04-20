#ifndef __RULES_H
#define __RULES_H

#include "symbol.h"
#include "types.h"

/* Program */
programValue *Manage_program(stmtListValue *);

/* Statement list */
stmtListValue *Manage_stmtList_stmt(stmtListValue *, stmtValue *);

stmtListValue *Manage_stmtList();

/* Statements */
stmtValue *Manage_stmt_expr(exprValue *);

stmtValue *Manage_stmt_ifstmt(ifstmtValue *);

stmtValue *Manage_stmt_whilestmt(whilestmtValue *);

stmtValue *Manage_stmt_forstmt(forstmtValue *);

stmtValue *Manage_stmt_returnstmt(returnstmtValue *);

stmtValue *Manage_stmt_break();

stmtValue *Manage_stmt_continue();

stmtValue *Manage_stmt_block(blockValue *);

stmtValue *Manage_stmt_funcdef(funcdefValue *);

stmtValue *Manage_stmt_semicolon();

/* Expressions */
exprValue *Manage_expr_assignexpr(exprValue *);

exprValue *Manage_expr_expr_PLUS_expr(exprValue *, exprValue *);

exprValue *Manage_expr_expr_MINUS_expr(exprValue *, exprValue *);

exprValue *Manage_expr_expr_MUL_expr(exprValue *, exprValue *);

exprValue *Manage_expr_expr_DIV_expr(exprValue *, exprValue *);

exprValue *Manage_expr_expr_MOD_expr(exprValue *, exprValue *);

exprValue *Manage_expr_expr_GT_expr(exprValue *, exprValue *);

exprValue *Manage_expr_expr_GE_expr(exprValue *, exprValue *);

exprValue *Manage_expr_expr_LT_expr(exprValue *, exprValue *);

exprValue *Manage_expr_expr_LE_expr(exprValue *, exprValue *);

exprValue *Manage_expr_expr_EQUAL_expr(exprValue *, exprValue *);

exprValue *Manage_expr_expr_NEQUAL_expr(exprValue *, exprValue *);

exprValue *Manage_expr_expr_AND_expr(exprValue *, exprValue *);

exprValue *Manage_expr_expr_OR_expr(exprValue *, exprValue *);

exprValue *Manage_expr_term(exprValue *);

/* Terms */
exprValue *Manage_term_LPexprRP(exprValue *);

exprValue *Manage_term_notexpr(exprValue *);

exprValue *Manage_term_PPlval(exprValue *);

exprValue *Manage_term_lvaluePP(exprValue *);

exprValue *Manage_term_MMlval(exprValue *);

exprValue *Manage_term_lvalueMM(exprValue *);

exprValue *Manage_term_primary(exprValue *);

exprValue *Manage_term_minusexpr(exprValue *);

/* Assign expression */
exprValue *Manage_assignexpr_lvalueASSIGNexpr(exprValue *, exprValue *);

/* Primary */
exprValue *Manage_primary_lvalue(exprValue *);

exprValue *Manage_primary_call(exprValue *);

exprValue *Manage_primary_objectdef(exprValue *);

exprValue *Manage_primary_LPfuncdefRP(funcdefValue *);

exprValue *Manage_primary_const(exprValue *);

/* lvalue */
exprValue *Manage_lvalue_id(std::string);

exprValue *Manage_lvalue_localid(std::string);

exprValue *Manage_lvalue_globalid(std::string);

exprValue *Manage_lvalue_member(exprValue *);

/* Members */
exprValue *Manage_member_lvalueDOTid(exprValue *, std::string);

exprValue *Manage_member_lvalueLSBexprRSB(exprValue *, exprValue *);

exprValue *Manage_member_callDOTid(exprValue *, std::string);

exprValue *Manage_member_callLSBexprRSB(exprValue *, exprValue *);

/* Calls */
exprValue *Manage_call_callLPelistRP(exprValue *, elistValue *);

exprValue *Manage_call_lvaluecallsuffix(exprValue *, callsuffixValue *);

exprValue *Manage_call_LPfuncdefRPLPelistRP(funcdefValue *, elistValue *);

/* Call suffix */
callsuffixValue *Manage_callsuffix_normcall(normcallValue *);

callsuffixValue *Manage_callsuffix_methodcall(methodcallValue *);

/* Normal call */
normcallValue *Manage_normcall_LPelistRP(elistValue *);

/* Method call */
methodcallValue *Manage_methodcall_DDOTidLPelistRP(std::string, elistValue *);

/* elist */
elistValue *Manage_elist_exprOptRpt(exprOptRptValue *);

elistValue *Manage_elist();

/* Expression optional and repeatable */
exprOptRptValue *Manage_exprOR_exprOR(exprValue *, exprOptRptValue *);

exprOptRptValue *Manage_exprOR_expr(exprValue *);

/* Objectdef */
exprValue *Manage_objectdef_LSBelistRSB(elistValue *);

exprValue *Manage_objectdef_LSBindexedRSB(indexedValue *);

/* Indexed */
indexedValue *Manage_indexed(indelemlistValue *);

/* Indexed element list */
indelemlistValue *Manage_indelemlist(indexedelemValue *, indelemlistValue *);

indelemlistValue *Manage_indelemlist_indexedelem(indexedelemValue *);

indexedelemValue *Manage_indexedelem_LCB_expr_COLON_expr_RCB(exprValue *, exprValue *);

/* Block */
blockValue *Manage_block_LCBstmtRCB(stmtListValue *);

/* Funcdef */
Symbol *Manage_funcprefix(std::string);

void Manage_funcargs(idlistValue *);

funcdefValue *Manage_funcdef_id(std::string, idlistValue *, blockValue *);

funcdefValue *Manage_funcdef(idlistValue *, blockValue *);

std::string newTmpFuncname();

/* Constants */
exprValue *Manage_const_int(int);

exprValue *Manage_const_real(double);

exprValue *Manage_const_string(std::string);

exprValue *Manage_const_nil();

exprValue *Manage_const_true();

exprValue *Manage_const_false();

/* ID list */
idlistValue *Manage_idlist_ID(std::string);

idlistValue *Manage_idlist_idlist_comma_id(idlistValue *, std::string);

idlistValue *Manage_idlist();

/* If statement */
ifstmtValue *Manage_ifstmt(exprValue *, stmtValue *, elseValue *);

/* else */
elseValue *Manage_else_stmt(stmtValue *);

elseValue *Manage_else();

/* While statement */
whilestmtValue *Manage_whilestmt(exprValue *, stmtValue *);

/* For statement */
forstmtValue *Manage_for(elistValue *, exprValue *, elistValue *, stmtValue *);

/* Return statement */
returnstmtValue *Manage_returnstmt(retValue *);

/* Return */
retValue *Manage_ret_expr(exprValue *);

retValue *Manage_ret();
#endif /* __RULES_H */