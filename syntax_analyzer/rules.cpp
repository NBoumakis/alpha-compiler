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

static exprValue *make_call(exprValue *lvalue, exprList elist_r) {
    exprValue *func = emit_iftableitem(lvalue);

    for (auto expr = elist_r->rbegin(); expr != elist_r->rend(); ++expr) {
        emit(param_iop, *expr, nullptr, nullptr);
    }

    emit(call_iop, func, nullptr, nullptr);

    exprValue *result = new exprValue();
    result->valType = varExpr_T;

    result->symbolVal = newTempvar();
    emit(get_retval_iop, result, nullptr, nullptr);

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

void check_arithm(exprValue *expr) {
    if (expr->valType == constboolExpr_T ||
        expr->valType == conststringExpr_T ||
        expr->valType == nilExpr_T ||
        expr->valType == newtableExpr_T ||
        expr->valType == userfuncExpr_T ||
        expr->valType == libfuncExpr_T ||
        expr->valType == boolexprExpr_T) {
        std::cerr << BRED "Illegal expression used in line " << yylineno << RST << std::endl;
    }
}

bool valid_op_expr(exprValue *expr) {
    return !(expr->valType == userfuncExpr_T || expr->valType == libfuncExpr_T ||
             expr->valType == boolexprExpr_T || expr->valType == newtableExpr_T ||
             expr->valType == constboolExpr_T || expr->valType == conststringExpr_T ||
             expr->valType == nilExpr_T);
}

static exprValue *expr_op_emit(iopcode op, exprValue *expr_left, exprValue *expr_right) {
    exprValue *expr_res = new exprValue();

    if (valid_op_expr(expr_left) && valid_op_expr(expr_right)) {
        expr_res->valType = arithmexprExpr_T;

        expr_res->symbolVal = newTempvar();
        emit(op, expr_res, expr_left, expr_right);

    } else {
        std::cerr << BRED "Invalid operation between " << expr_left->to_string() << " (" << expr_left->type_string() << ") and "
                  << expr_right->to_string() << " (" << expr_right->type_string() << ") in line " << yylineno << RST << std::endl;

        expr_res->valType = nilExpr_T;
    }

    return expr_res;
}

static exprValue *expr_relop_emit(iopcode relop, exprValue *expr_left, exprValue *expr_right) {
    exprValue *expr_res = new exprValue();

    if (valid_op_expr(expr_left) && valid_op_expr(expr_right)) {
        expr_res->valType = boolexprExpr_T;
        expr_res->symbolVal = newTempvar();

        expr_res->truelist = newlist(nextQuadLabel());
        expr_res->falselist = newlist(nextQuadLabel() + 1);

        emit(relop, expr_left, expr_right, 0UL);
        emit(jump_iop, 0);
    } else {
        std::cerr << BRED "Invalid relational operation between " << expr_left->to_string() << " (" << expr_left->type_string() << ") and "
                  << expr_right->to_string() << " (" << expr_right->type_string() << ") in line " << yylineno << RST << std::endl;

        expr_res->valType = nilExpr_T;
    }

    return expr_res;
}

static bool isCompileBool(exprValue *expr) {
    return (expr->valType == nilExpr_T ||
            expr->valType == libfuncExpr_T ||
            expr->valType == userfuncExpr_T ||
            expr->valType == constnumExpr_T ||
            expr->valType == constboolExpr_T ||
            expr->valType == conststringExpr_T ||
            expr->valType == newtableExpr_T);
}

unsigned long newlist(unsigned long i) {
    quad_vector[i].label = 0;
    return i;
}

unsigned long merge_list(unsigned long l1, unsigned long l2) {
    if (!l1)
        return l2;

    else if (!l2)
        return l1;
    else {
        int i = l1;
        while (quad_vector[i].label)
            i = quad_vector[i].label;
        quad_vector[i].label = l2;
        return l1;
    }
}

stmtValue *Manage_stmtList_stmtList_stmt(stmtValue *nextStmts, stmtValue *stmt) {
    stmtValue *stmtlist = new stmtValue();

    stmtlist->breaklist = merge_list(nextStmts->breaklist, stmt->breaklist);
    stmtlist->contlist = merge_list(nextStmts->contlist, stmt->contlist);
    stmtlist->returnlist = merge_list(nextStmts->returnlist, stmt->returnlist);

    return stmtlist;
}

stmtValue *Manage_stmtList_stmt() {
    stmtValue *stmt = new stmtValue();

    stmt->breaklist = 0;
    stmt->contlist = 0;
    stmt->returnlist = 0;

    return stmt;
}

/* Statements */
stmtValue *Manage_stmt_expr(exprValue *expr) {
    resettemp();

    stmtValue *stmt = new stmtValue();

    stmt->breaklist = 0;
    stmt->contlist = 0;

    return stmt;
}

stmtValue *Manage_stmt_ifstmt(stmtValue *ifstmt) {
    return ifstmt;
}

stmtValue *Manage_stmt_whilestmt(stmtValue *whilestmt) {
    whilestmt->breaklist = 0;
    whilestmt->contlist = 0;

    return whilestmt;
}

stmtValue *Manage_stmt_for(stmtValue *forstmt) {
    forstmt->breaklist = 0;
    forstmt->contlist = 0;

    return forstmt;
}

stmtValue *Manage_stmt_RETURN_ret_SEMICOLON() {
    if (funcDepth == 0) {
        std::cerr << BRED "Cannot use return statement outside of function in line " << yylineno << RST << std::endl;
    }

    stmtValue *returnVal = new stmtValue();
    returnVal->breaklist = 0;
    returnVal->contlist = 0;
    returnVal->returnlist = newlist(nextQuadLabel());

    emit(jump_iop, 0);

    return returnVal;
}

stmtValue *Manage_stmt_break() {
    stmtValue *breakVal = new stmtValue();

    breakVal->contlist = 0;

    if (loopcounter > 0) {
        breakVal->breaklist = newlist(nextQuadLabel());
    } else {
        std::cerr << BRED "Cannot use break statement while not a loop in line " << yylineno << RST << std::endl;
    }

    emit(jump_iop, 0);

    return breakVal;
}

stmtValue *Manage_stmt_continue() {
    stmtValue *contVal = new stmtValue();
    contVal->breaklist = 0;

    if (loopcounter > 0) {
        contVal->contlist = newlist(nextQuadLabel());
    } else {
        std::cerr << BRED "Cannot use continue statement while not a loop in line " << yylineno << RST << std::endl;
    }

    emit(jump_iop, 0);

    return contVal;
}

stmtValue *Manage_stmt_block(stmtValue *block) {
    return block;
}

stmtValue *Manage_stmt_funcdef(Function *funcdef) {
    stmtValue *stmt = new stmtValue();

    stmt->breaklist = 0;
    stmt->contlist = 0;

    return stmt;
}

stmtValue *Manage_stmt_semicolon() {
    resettemp();

    stmtValue *stmt = new stmtValue();

    stmt->breaklist = 0;
    stmt->contlist = 0;

    return stmt;
}

/* Expressions */
exprValue *Manage_expr_assignexpr(exprValue *assignexpr) {
    return assignexpr;
}

exprValue *Manage_expr_expr_PLUS_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *expr_res;

    if (exprLeft->valType == constnumExpr_T && exprRight->valType == constnumExpr_T) {
        expr_res = new exprValue();
        expr_res->valType = constnumExpr_T;

        expr_res->numConstval = exprLeft->numConstval + exprRight->numConstval;
    } else {
        expr_res = expr_op_emit(add_iop, exprLeft, exprRight);
    }

    return expr_res;
}

exprValue *Manage_expr_expr_MINUS_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *expr_res;

    if (exprLeft->valType == constnumExpr_T && exprRight->valType == constnumExpr_T) {
        expr_res = new exprValue();
        expr_res->valType = constnumExpr_T;

        expr_res->numConstval = exprLeft->numConstval - exprRight->numConstval;
    } else {
        expr_res = expr_op_emit(sub_iop, exprLeft, exprRight);
    }

    return expr_res;
}

exprValue *Manage_expr_expr_MUL_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *expr_res;

    if (exprLeft->valType == constnumExpr_T && exprRight->valType == constnumExpr_T) {
        expr_res = new exprValue();
        expr_res->valType = constnumExpr_T;

        expr_res->numConstval = exprLeft->numConstval * exprRight->numConstval;
    } else {
        expr_res = expr_op_emit(mul_iop, exprLeft, exprRight);
    }

    return expr_res;
}

exprValue *Manage_expr_expr_DIV_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *expr_res;

    if (exprLeft->valType == constnumExpr_T && exprRight->valType == constnumExpr_T) {
        expr_res = new exprValue();
        expr_res->valType = constnumExpr_T;

        if (exprRight->numConstval == 0) {
            std::cerr << BBLU "Division by zero in line " << yylineno << RST << std::endl;
            expr_res->valType = nilExpr_T;
        } else {
            expr_res->numConstval = exprLeft->numConstval / exprRight->numConstval;
        }
    } else {
        expr_res = expr_op_emit(div_iop, exprLeft, exprRight);
    }

    return expr_res;
}

exprValue *Manage_expr_expr_MOD_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *expr_res;

    if (exprLeft->valType == constnumExpr_T && exprRight->valType == constnumExpr_T) {
        expr_res = new exprValue();
        expr_res->valType = constnumExpr_T;

        if (exprRight->numConstval == 0) {
            std::cerr << BBLU "Modulo with zero in line " << yylineno << RST << std::endl;
            expr_res->valType = nilExpr_T;
        } else {
            expr_res->numConstval = static_cast<int>(exprLeft->numConstval) % static_cast<int>(exprRight->numConstval);
        }
    } else {
        expr_res = expr_op_emit(mod_iop, exprLeft, exprRight);
    }

    return expr_res;
}

exprValue *Manage_expr_expr_GT_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *expr_res;

    if (exprLeft->valType == constnumExpr_T && exprRight->valType == constnumExpr_T) {
        expr_res = new exprValue();
        expr_res->valType = boolexprExpr_T;

        expr_res->boolConstVal = (exprLeft->numConstval > exprRight->numConstval);
    } else {
        expr_res = expr_relop_emit(if_greater_iop, exprLeft, exprRight);
    }

    return expr_res;
}

exprValue *Manage_expr_expr_GE_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *expr_res;

    if (exprLeft->valType == constnumExpr_T && exprRight->valType == constnumExpr_T) {
        expr_res = new exprValue();
        expr_res->valType = constboolExpr_T;

        expr_res->boolConstVal = (exprLeft->numConstval >= exprRight->numConstval);
    } else {
        expr_res = expr_relop_emit(if_greater_eq_iop, exprLeft, exprRight);
    }

    return expr_res;
}

exprValue *Manage_expr_expr_LT_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *expr_res;

    if (exprLeft->valType == constnumExpr_T && exprRight->valType == constnumExpr_T) {
        expr_res = new exprValue();
        expr_res->valType = constboolExpr_T;

        expr_res->boolConstVal = (exprLeft->numConstval < exprRight->numConstval);
    } else {
        expr_res = expr_relop_emit(if_less_iop, exprLeft, exprRight);
    }

    return expr_res;
}

exprValue *Manage_expr_expr_LE_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *expr_res;

    if (exprLeft->valType == constnumExpr_T && exprRight->valType == constnumExpr_T) {
        expr_res = new exprValue();
        expr_res->valType = constboolExpr_T;

        expr_res->boolConstVal = (exprLeft->numConstval <= exprRight->numConstval);
    } else {
        expr_res = expr_relop_emit(if_less_eq_iop, exprLeft, exprRight);
    }

    return expr_res;
}

exprValue *Manage_expr_expr_EQUAL_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *expr_res;

    if (exprLeft->valType == constnumExpr_T && exprRight->valType == constnumExpr_T) {
        expr_res = new exprValue();
        expr_res->valType = constboolExpr_T;

        expr_res->boolConstVal = (exprLeft->numConstval == exprRight->numConstval);
    } else {
        expr_res = expr_relop_emit(if_eq_iop, exprLeft, exprRight);
    }
    return expr_res;
}

exprValue *Manage_expr_expr_NEQUAL_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *expr_res;

    if (exprLeft->valType == constnumExpr_T && exprRight->valType == constnumExpr_T) {
        expr_res = new exprValue();
        expr_res->valType = constboolExpr_T;

        expr_res->boolConstVal = (exprLeft->numConstval != exprRight->numConstval);
    } else {
        expr_res = expr_relop_emit(if_not_eq_iop, exprLeft, exprRight);
    }

    return expr_res;
}

exprValue *Manage_expr_expr_AND_expr(exprValue *exprLeft, exprValue *exprRight, unsigned long l1) {
    exprValue *expr_res = new exprValue();

    if (isCompileBool(exprLeft) && isCompileBool(exprRight)) {
        expr_res->valType = constboolExpr_T;

        expr_res->boolConstVal = static_cast<bool>(*exprLeft) && static_cast<bool>(*exprRight);
    } else if (isCompileBool(exprLeft) && !exprLeft->boolConstVal) {
        expr_res->valType = constboolExpr_T;

        expr_res->boolConstVal = false;
    } else if (isCompileBool(exprRight) && !exprRight->boolConstVal) {
        expr_res->valType = constboolExpr_T;

        expr_res->boolConstVal = false;
    } else {
        patchList(exprLeft->truelist, l1);

        expr_res->valType = boolexprExpr_T;
        expr_res->symbolVal = newTempvar();

        expr_res->truelist = exprRight->truelist;
        expr_res->falselist = merge_list(exprLeft->falselist, exprRight->falselist);
    }

    return expr_res;
}

exprValue *Manage_expr_expr_OR_expr(exprValue *exprLeft, exprValue *exprRight, unsigned long l1) {
    exprValue *expr_res = new exprValue();

    if (isCompileBool(exprLeft) && isCompileBool(exprRight)) {
        expr_res->valType = constboolExpr_T;

        expr_res->boolConstVal = static_cast<bool>(*exprLeft) || static_cast<bool>(*exprRight);
    } else if (isCompileBool(exprLeft) && exprLeft->boolConstVal) {
        expr_res->valType = constboolExpr_T;

        expr_res->boolConstVal = true;
    } else if (isCompileBool(exprRight) && exprRight->boolConstVal) {
        expr_res->valType = constboolExpr_T;

        expr_res->boolConstVal = true;
    } else {
        patchList(exprLeft->falselist, l1);

        expr_res->valType = boolexprExpr_T;
        expr_res->symbolVal = newTempvar();

        expr_res->truelist = merge_list(exprLeft->truelist, exprRight->truelist);
        expr_res->falselist = exprRight->falselist;
    }

    return expr_res;
}

exprValue *Manage_expr_term(exprValue *term) {
    return term;
}

/* Terms */
exprValue *Manage_term_LPexprRP(exprValue *expr) {
    return expr;
}

exprValue *Manage_term_notexpr(exprValue *expr) {
    exprValue *termVal = new exprValue();

    if (isCompileBool(expr)) {
        termVal->valType = constboolExpr_T;
        termVal->boolConstVal = !(static_cast<bool>(*expr));
    } else {
        termVal->valType = boolexprExpr_T;
        termVal->symbolVal = newTempvar();

        termVal->falselist = expr->truelist;
        termVal->truelist = expr->falselist;
    }

    return termVal;
}

exprValue *Manage_term_PPlval(exprValue *lvalue) {
    exprValue *termVal;

    if (lvalue->valType == varExpr_T) {
        if (lvalue->symbolVal->type == USER_FUNC ||
            lvalue->symbolVal->type == LIB_FUNC) {
            std::cerr << BRED "Invalid preincrement of "
                      << type_names[lvalue->symbolVal->type]
                      << " \"" << lvalue->symbolVal->name
                      << "\" in line " << yylineno << "." RST << std::endl;
        }
    }

    check_arithm(lvalue);

    exprValue *const_num = new exprValue();
    const_num->valType = constnumExpr_T;
    const_num->numConstval = 1;

    if (lvalue->valType == TableitemExpr_T) {
        termVal = emit_iftableitem(lvalue);
        emit(add_iop, termVal, termVal, const_num);
        emit(table_setelem_iop, termVal, lvalue, lvalue->indexVal);
    } else {
        emit(add_iop, lvalue, lvalue, const_num);
        termVal = new exprValue();
        termVal->valType = arithmexprExpr_T;

        termVal->symbolVal = newTempvar();
        emit(assign_iop, termVal, lvalue, nullptr);
    }

    return termVal;
}

exprValue *Manage_term_lvaluePP(exprValue *lvalue) {
    exprValue *termVal;

    if (lvalue->valType == varExpr_T) {
        if (lvalue->symbolVal->type == USER_FUNC ||
            lvalue->symbolVal->type == LIB_FUNC) {
            std::cerr << BRED "Invalid postincrement of "
                      << type_names[lvalue->symbolVal->type]
                      << " \"" << lvalue->symbolVal->name
                      << "\" in line " << yylineno << "." RST << std::endl;
        }
    }

    check_arithm(lvalue);
    termVal = new exprValue();
    termVal->valType = varExpr_T;

    termVal->symbolVal = newTempvar();

    exprValue *const_num = new exprValue();

    const_num->valType = constnumExpr_T;
    const_num->numConstval = 1;

    if (lvalue->valType == TableitemExpr_T) {
        exprValue *val = emit_iftableitem(lvalue);

        emit(assign_iop, termVal, val, nullptr);
        emit(add_iop, val, val, const_num);
        emit(table_setelem_iop, val, lvalue, lvalue->indexVal);
    } else {
        emit(assign_iop, termVal, lvalue, nullptr);
        emit(add_iop, lvalue, lvalue, const_num);
    }

    return termVal;
}

exprValue *Manage_term_MMlval(exprValue *lvalue) {
    exprValue *termVal;

    if (lvalue->valType == varExpr_T) {
        if (lvalue->symbolVal->type == USER_FUNC ||
            lvalue->symbolVal->type == LIB_FUNC) {
            std::cerr << BRED "Invalid predecrement of "
                      << type_names[lvalue->symbolVal->type]
                      << " \"" << lvalue->symbolVal->name
                      << "\" in line " << yylineno << "." RST << std::endl;
        }
    }

    check_arithm(lvalue);

    exprValue *const_num = new exprValue();
    const_num->valType = constnumExpr_T;
    const_num->numConstval = 1;

    if (lvalue->valType == TableitemExpr_T) {
        termVal = emit_iftableitem(lvalue);
        emit(sub_iop, termVal, termVal, const_num);
        emit(table_setelem_iop, termVal, lvalue, lvalue->indexVal);
    } else {
        emit(sub_iop, lvalue, lvalue, const_num);
        termVal = new exprValue();
        termVal->valType = arithmexprExpr_T;

        termVal->symbolVal = newTempvar();
        emit(assign_iop, termVal, lvalue, nullptr);
    }

    return termVal;
}

exprValue *Manage_term_lvalueMM(exprValue *lvalue) {
    exprValue *termVal;

    if (lvalue->valType == varExpr_T) {
        if (lvalue->symbolVal->type == USER_FUNC ||
            lvalue->symbolVal->type == LIB_FUNC) {
            std::cerr << BRED "Invalid postdecrement of "
                      << type_names[lvalue->symbolVal->type]
                      << " \"" << lvalue->symbolVal->name
                      << "\" in line " << yylineno << "." RST << std::endl;
        }
    }

    check_arithm(lvalue);
    termVal = new exprValue();
    termVal->valType = varExpr_T;

    termVal->symbolVal = newTempvar();

    exprValue *const_num = new exprValue();

    const_num->valType = constnumExpr_T;
    const_num->numConstval = 1;

    if (lvalue->valType == TableitemExpr_T) {
        exprValue *val = emit_iftableitem(lvalue);

        emit(assign_iop, termVal, val, nullptr);
        emit(sub_iop, val, val, const_num);
        emit(table_setelem_iop, val, lvalue, lvalue->indexVal);
    } else {
        emit(assign_iop, termVal, lvalue, nullptr);
        emit(sub_iop, lvalue, lvalue, const_num);
    }

    return termVal;
}

exprValue *Manage_term_primary(exprValue *primary) {
    return primary;
}

exprValue *Manage_term_minusexpr(exprValue *expr) {
    exprValue *termVal = new exprValue();
    termVal->valType = arithmexprExpr_T;

    check_arithm(expr);

    termVal->symbolVal = newTempvar();
    emit(uminus_iop, termVal, expr, nullptr);

    return termVal;
}

/* Assign expression */
exprValue *Manage_assignexpr_lvalueASSIGNexpr(exprValue *lvalue, exprValue *expr) {
    exprValue *assignexprVal;

    if (lvalue->valType == varExpr_T) {
        Symbol *symbol = lvalue->symbolVal;

        if (funcDepth != symbol->funcDepth &&
            static_cast<Variable *>(symbol)->scope != 0) {
            std::cerr << BRED "Inaccessible " << type_names[symbol->type] << " \"" << symbol->name << "\" in line " << yylineno << RST << std::endl;
        } else {
            emit(assign_iop, lvalue, expr, nullptr);

            assignexprVal = new exprValue();
            assignexprVal->valType = assignexprExpr_T;

            assignexprVal->symbolVal = newTempvar();
            emit(assign_iop, assignexprVal, lvalue, nullptr);
        }
    } else if (lvalue->valType == TableitemExpr_T) {
        emit(table_setelem_iop, expr, lvalue, lvalue->indexVal);

        assignexprVal = emit_iftableitem(lvalue);
        assignexprVal->valType = assignexprExpr_T;
    }

    return assignexprVal;
}

/* Primary */
exprValue *Manage_primary_lvalue(exprValue *lvalue) {
    exprValue *primaryValueVal = lvalue;

    if (lvalue->valType != nilExpr_T) {

        Symbol *symbol = lvalue->symbolVal;
        if (symbol->scope == 0 ||
            symbol->type == USER_FUNC ||
            symbol->type == LIB_FUNC ||
            funcDepth == symbol->funcDepth) {

            primaryValueVal = emit_iftableitem(lvalue);
        } else {
            std::cerr << BRED "Inaccessible " << type_names[symbol->type] << " \"" << symbol->name << "\" in line " << yylineno << RST << std::endl;
            lvalue->valType = nilExpr_T;
            primaryValueVal = lvalue;
        }
    }

    return primaryValueVal;
}

exprValue *Manage_primary_call(exprValue *call) {
    return call;
}

exprValue *Manage_primary_objectdef(exprValue *objdef) {
    return objdef;
}

exprValue *Manage_primary_LPfuncdefRP(Function *funcdef) {
    exprValue *primaryVal = new exprValue();
    primaryVal->valType = userfuncExpr_T;
    primaryVal->symbolVal = funcdef;

    return primaryVal;
}

exprValue *Manage_primary_const(exprValue *constVal) {
    return constVal;
}

/* lvalue */
static exprValue *lvalue_expr(Symbol *symbol) {
    assert(symbol);

    exprValue *e = new exprValue();

    e->symbolVal = symbol;

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
            newStructVal->valType = nilExpr_T;
        }
    } else {
        newStructVal = lvalue_expr(symbol);
    }

    return newStructVal;
}

exprValue *Manage_lvalue_globalid(std::string id) {
    exprValue *newStructVal;

    auto symbol = symbolTableObj.lookup_scope(id, 0);

    if (symbol == nullptr) {
        std::cerr << BRED "Undefined reference to global symbol \"" << id << "\" in line " << yylineno << "." RST << std::endl;

        newStructVal = new exprValue();
        newStructVal->valType = nilExpr_T;
    } else {
        newStructVal = lvalue_expr(symbol);
    }

    return newStructVal;
}

exprValue *Manage_lvalue_member(exprValue *member) {
    return member;
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
    return member_item(call, id);
}

exprValue *Manage_member_callLSBexprRSB(exprValue *call, exprValue *expr) {
    exprValue *tableitem;

    call = emit_iftableitem(call);

    tableitem = new exprValue();
    tableitem->valType = TableitemExpr_T;
    tableitem->symbolVal = call->symbolVal;

    tableitem->indexVal = expr;

    return tableitem;
}

/* Calls */
exprValue *Manage_call_callLPelistRP(exprValue *call, exprList elist) {
    exprValue *callVal = make_call(call, elist);
    return callVal;
}

exprValue *Manage_call_lvaluecallsuffix(exprValue *lvalue, callValue *callsuffix) {
    lvalue = emit_iftableitem(lvalue);
    if (callsuffix->method) {
        exprValue *t = lvalue;
        exprList p = callsuffix->elist;

        lvalue = emit_iftableitem(member_item(t, callsuffix->name));

        p->push_front(t);
    }

    return make_call(lvalue, callsuffix->elist);
}

exprValue *Manage_call_LPfuncdefRPLPelistRP(Function *funcdef, exprList elist) {
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
callValue *Manage_normcall_LPelistRP(exprList elist) {
    callValue *normcallVal = new callValue();

    normcallVal->elist = elist;
    normcallVal->method = 0;
    normcallVal->name = "";

    return normcallVal;
}

/* Method call */
callValue *Manage_methodcall_DDOTidLPelistRP(std::string id, exprList elist) {
    callValue *methodcallVal = new callValue();

    methodcallVal->elist = elist;
    methodcallVal->method = true;
    methodcallVal->name = id;

    return methodcallVal;
}

/* elist */
exprList Manage_elist_exprOptRpt(exprList exprOptRpt) {
    return exprOptRpt;
}

exprList Manage_elist() {
    return new std::list<exprValue *>();
}

/* Expression optional and repeatable */
void Manage_exprOptRpt_expr_exprOptRpt(exprValue *expr, exprList &list) {
    list->push_back(expr);
}

void Manage_exprOptRpt_expr(exprValue *expr, exprList &list) {
    list = new std::list<exprValue *>();

    list->push_back(expr);
}

/* Objectdef */
exprValue *Manage_objectdef_LSBelistRSB(exprList elist) {
    exprValue *objdefVal = new exprValue();
    objdefVal->valType = newtableExpr_T;

    objdefVal->symbolVal = newTempvar();
    emit(table_create_iop, objdefVal, nullptr, nullptr);

    unsigned long i = 0;
    for (auto &expr : *elist) {
        exprValue *constVal = new exprValue();
        constVal->valType = constnumExpr_T;
        constVal->numConstval = i++;

        emit(table_setelem_iop, expr, objdefVal, constVal);
    }

    return objdefVal;
}

exprValue *Manage_objectdef_LSBindexedRSB(indexedList indexed) {
    exprValue *objdefVal = new exprValue();
    objdefVal->valType = newtableExpr_T;

    objdefVal->symbolVal = newTempvar();
    emit(table_create_iop, objdefVal, nullptr, nullptr);

    for (auto indexedelem : *indexed) {
        emit(table_setelem_iop, indexedelem->first, objdefVal, indexedelem->second);

        delete indexedelem;
    }

    return objdefVal;
}

/* Indexed element list */
void Manage_indexed_indexedelem_COMMA_indexed(exprPair *elem, indexedList &indelemlist) {
    indelemlist->push_back(elem);
}

void Manage_indexed_indexedelem(indexedList &indexed_l, exprPair *elem) {
    indexed_l = new std::list<exprPair *>();

    indexed_l->push_back(elem);
}

exprPair *Manage_indexedelem_LCB_expr_COLON_expr_RCB(exprValue *key, exprValue *value) {
    exprPair *elemVal = new exprPair();

    elemVal->first = value;
    elemVal->second = key;

    return elemVal;
}

/* Block */
stmtValue *Manage_block_LCBstmtRCB(stmtValue *stmt) {
    return stmt;
}

/* Funcdef */
Function *Manage_funcprefix(std::string funcName) {
    Function *newFunc;
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
    }

    emit(jump_iop, 0);

    newFunc = new Function(funcName, scopeLevel, yylineno, funcDepth, USER_FUNC, currScopespaceOffset(), nextQuadLabel());

    symbolTableObj.insert(funcName, newFunc, scopeLevel);

    exprValue *funcprefix = new exprValue();
    funcprefix->valType = userfuncExpr_T;
    funcprefix->symbolVal = newFunc;

    emit(funcstart_iop, funcprefix, nullptr, nullptr);

    scopeOffsetStack.push(currScopespaceOffset());
    enterScopespace();
    resetFormalArgOffset();

    return newFunc;
}

unsigned long Manage_funcbody(stmtValue *block) {
    unsigned long scopeOffset = currScopespaceOffset();
    exitScopespace();

    patchList(block->returnlist, nextQuadLabel());

    return scopeOffset;
}

static bool check_funcargs(exprList &idlist) {
    std::set<std::string> argSet;

    for (auto &id : *idlist) {
        auto symbol_in_table = symbolTableObj.lookup_scope(id->strConstVal, scopeLevel);

        if (argSet.count(id->strConstVal) > 0) {
            std::cerr << BRED "Duplicate argument \"" << id << "\" in line " << yylineno << RST << std::endl;

            return false;
        } else if (isLibFunction(id->strConstVal)) {
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

        argSet.insert(id->strConstVal);
    }

    return true;
}

void Manage_funcargs(exprList &idlist) {
    ++scopeLevel;
    enterScopespace();

    if (check_funcargs(idlist)) {
        for (auto &id : *idlist) {
            Symbol *newArg = new Variable(id->strConstVal, scopeLevel, yylineno, funcDepth, currScopespace(), currScopespaceOffset());
            symbolTableObj.insert(newArg->name, newArg, scopeLevel);

            increaseCurrScopeOffset();
        }
    }

    resetFunctionLocalOffset();
    --scopeLevel;
}

Function *Manage_funcdef(Function *funcprefix, unsigned long funcbody) {
    if (funcprefix) {
        exitScopespace();
        funcprefix->totalLocals = funcbody;
        unsigned long offset = scopeOffsetStack.top();
        scopeOffsetStack.pop();
        restoreCurrScopeOffset(offset);

        exprValue *fpre_expr = new exprValue();
        fpre_expr->valType = userfuncExpr_T;
        fpre_expr->symbolVal = funcprefix;

        emit(funcend_iop, fpre_expr, nullptr, nullptr);
        patchLabel(funcprefix->iaddress - 1, nextQuadLabel());
        return funcprefix;
    } else {
        return nullptr;
    }
}

std::string newTmpFuncname() {
    static unsigned long long unnamed_function_counter = 0;

    std::string function_name = std::string("$f") + std::to_string(unnamed_function_counter++);

    return function_name;
}

/* Constants */
exprValue *Manage_const_int(int intVal) {
    exprValue *constVal = new exprValue();
    constVal->valType = constnumExpr_T;
    constVal->numConstval = intVal;
    return constVal;
}

exprValue *Manage_const_real(double doubleVal) {
    exprValue *constVal = new exprValue();
    constVal->valType = constnumExpr_T;
    constVal->numConstval = doubleVal;
    return constVal;
}

exprValue *Manage_const_string(std::string strVal) {
    exprValue *constVal = new exprValue();
    constVal->valType = conststringExpr_T;
    constVal->strConstVal = strVal;
    return constVal;
}

exprValue *Manage_const_nil() {
    exprValue *constVal = new exprValue();
    constVal->valType = nilExpr_T;

    return constVal;
}

exprValue *Manage_const_true() {
    exprValue *constVal = new exprValue();
    constVal->valType = constboolExpr_T;
    constVal->boolConstVal = true;
    return constVal;
}

exprValue *Manage_const_false() {
    exprValue *constVal = new exprValue();
    constVal->valType = constboolExpr_T;
    constVal->boolConstVal = false;
    return constVal;
}

/* ID list */
void Manage_idlist_ID(std::string id, exprList &list) {
    list = new std::list<exprValue *>();

    exprValue *id_expr = new exprValue();
    id_expr->valType = conststringExpr_T;

    id_expr->strConstVal = id;

    list->push_back(id_expr);
}

void Manage_idlist_idlist_comma_id(std::string id, exprList &list) {
    exprValue *id_expr = new exprValue();
    id_expr->valType = conststringExpr_T;

    id_expr->strConstVal = id;

    list->push_back(id_expr);
}

void Manage_idlist(exprList &list) {
    list = new std::list<exprValue *>();
}

/* If statement */
unsigned long Manage_ifprefix(exprValue *expr) {
    exprValue *constboolVal = new exprValue();
    constboolVal->valType = constboolExpr_T;

    constboolVal->boolConstVal = true;

    emit(if_eq_iop, expr, constboolVal, nextQuadLabel() + 2);

    unsigned long tmp_nextquad = nextQuadLabel();

    emit(jump_iop, 0);

    return tmp_nextquad;
}

stmtValue *Manage_ifstmt_ifprefix_stmt(unsigned long ifprefix, stmtValue *stmt) {
    patchLabel(ifprefix, nextQuadLabel());

    return stmt;
}

stmtValue *Manage_ifstmt_ifprefix_stmt_else_prefix_stmt(unsigned long ifprefix, stmtValue *true_stmt, unsigned long elseprefix, stmtValue *false_stmt) {
    stmtValue *stmt = new stmtValue();

    stmt->breaklist = merge_list(true_stmt->breaklist, false_stmt->breaklist);
    stmt->contlist = merge_list(true_stmt->contlist, false_stmt->contlist);
    stmt->returnlist = merge_list(true_stmt->returnlist, false_stmt->returnlist);

    delete true_stmt;
    delete false_stmt;

    patchLabel(ifprefix, elseprefix + 1);
    patchLabel(elseprefix, nextQuadLabel());

    return stmt;
}

/* else */
unsigned long Manage_elseprefix() {
    unsigned long nextquad = nextQuadLabel();

    emit(jump_iop, 0);

    return nextquad;
}

/* Loops helpers */
stmtValue *Manage_loopstart_stmt_loopend(stmtValue *stmt) {
    return stmt;
}

/* While statement */
unsigned long Manage_whilestart() {
    return nextQuadLabel();
}

unsigned long Manage_whilecond(exprValue *expr) {
    exprValue *constbool = new exprValue();
    constbool->valType = constboolExpr_T;
    constbool->boolConstVal = true;

    emit(if_eq_iop, expr, constbool, nextQuadLabel() + 2);

    unsigned long whilecond = nextQuadLabel();

    emit(jump_iop, 0);

    return whilecond;
}

stmtValue *Manage_while(unsigned long whilestart, unsigned long whilecond, stmtValue *stmt) {
    emit(jump_iop, whilestart);
    patchLabel(whilecond, nextQuadLabel());
    patchList(stmt->breaklist, nextQuadLabel());
    patchList(stmt->contlist, whilestart);

    return stmt;
}

/* For statement */
unsigned long Manage_n() {
    unsigned long nextquad = nextQuadLabel();

    emit(jump_iop, 0);

    return nextquad;
}

unsigned long Manage_m() {
    return nextQuadLabel();
}

forprefixValue *Manage_forprefix(unsigned long m, exprValue *expr) {
    forprefixValue *forprefix = new forprefixValue();

    forprefix->test = m;
    forprefix->enter = nextQuadLabel();

    exprValue *constbool = new exprValue();
    constbool->valType = constboolExpr_T;
    constbool->boolConstVal = true;

    emit(if_eq_iop, expr, constbool);

    return forprefix;
}

stmtValue *Manage_for(forprefixValue *forprefix, unsigned long n1, unsigned long n2, unsigned long n3, stmtValue *stmt) {
    patchLabel(forprefix->enter, n2 + 1);
    patchLabel(n1, nextQuadLabel());
    patchLabel(n2, forprefix->test);
    patchLabel(n3, n1 + 1);

    patchList(stmt->breaklist, nextQuadLabel());
    patchList(stmt->contlist, n1 + 1);

    return stmt;
}

/* Return */
void Manage_ret_expr(exprValue *expr) {
    emit(ret_iop, expr, nullptr);
}

void Manage_ret() {
    emit(ret_iop, nullptr, nullptr);
}