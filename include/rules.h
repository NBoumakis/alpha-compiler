#ifndef __RULES_H
#define __RULES_H

#include "symbol.h"
#include "types.h"

/* Statement list */
stmtValue *Manage_stmtList_stmtList_stmt(stmtValue *, stmtValue *);

stmtValue *Manage_stmtList_stmt(stmtValue *);

/* Statements */
stmtValue *Manage_stmt_expr(exprValue *);

stmtValue *Manage_stmt_ifstmt(stmtValue *ifstmt);

stmtValue *Manage_stmt_whilestmt();

stmtValue *Manage_stmt_for();

stmtValue *Manage_stmt_returnstmt(returnstmtValue *);

stmtValue *Manage_stmt_break();

stmtValue *Manage_stmt_continue();

stmtValue *Manage_stmt_block(blockValue *);

stmtValue *Manage_stmt_funcdef(Function *);

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

exprValue *Manage_primary_LPfuncdefRP(Function *);

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
exprValue *Manage_call_callLPelistRP(exprValue *, exprValue *);

exprValue *Manage_call_lvaluecallsuffix(exprValue *, callValue *);

exprValue *Manage_call_LPfuncdefRPLPelistRP(Function *, exprValue *);

/* Call suffix */
callValue *Manage_callsuffix_normcall(callValue *);

callValue *Manage_callsuffix_methodcall(callValue *);

/* Normal call */
callValue *Manage_normcall_LPelistRP(exprValue *);

/* Method call */
callValue *Manage_methodcall_DDOTidLPelistRP(std::string, exprValue *);

/* elist */
exprValue *Manage_elist_exprOptRpt(exprValue *);

exprValue *Manage_elist();

/* Expression optional and repeatable */
exprValue *Manage_exprOptRpt_expr_exprOptRpt(exprValue *, exprValue *);

exprValue *Manage_exprOptRpt_expr(exprValue *);

/* Objectdef */
exprValue *Manage_objectdef_LSBelistRSB(exprValue *);

exprValue *Manage_objectdef_LSBindexedRSB(exprOptRptValue *);

/* Indexed */
exprOptRptValue *Manage_indexed_indexedelem_COMMA_indexed(exprOptRptValue *, exprOptRptValue *);

exprOptRptValue *Manage_indexed_indexedelem(exprOptRptValue *);

exprOptRptValue *Manage_indexedelem_LCB_expr_COLON_expr_RCB(exprValue *, exprValue *);

/* Block */
blockValue *Manage_block_LCBstmtRCB(stmtValue *);

/* Funcdef */
Function *Manage_funcprefix(std::string);

unsigned long Manage_funcbody();

void Manage_funcargs(idlistValue *);

Function *Manage_funcdef(Function *, unsigned long);

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
unsigned long Manage_ifprefix(exprValue *);

stmtValue *Manage_ifstmt_ifprefix_stmt(unsigned long, stmtValue *);

stmtValue *Manage_ifstmt_ifprefix_stmt_else_prefix_stmt(unsigned long, stmtValue *, unsigned long, stmtValue *);

/* else */
unsigned long Manage_elseprefix();

/* While statement */
unsigned long Manage_whilestart();

unsigned long Manage_whilecond(exprValue *expr);

void Manage_while(unsigned long, unsigned long, stmtValue *);

/* For statement */
unsigned long Manage_n();

unsigned long Manage_m();

forprefixValue *Manage_forprefix(unsigned long, exprValue *);

void Manage_for(forprefixValue *, unsigned long, unsigned long, unsigned long, stmtValue *);

/* Return statement */
returnstmtValue *Manage_returnstmt(retValue *);

/* Return */
retValue *Manage_ret_expr(exprValue *);

retValue *Manage_ret();
#endif /* __RULES_H */