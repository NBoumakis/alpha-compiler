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
extern unsigned comp_err;

unsigned long newlist(unsigned long i) {
    return i;
}

static exprValue *make_call(exprValue *lvalue, exprList elist_r) {
    exprValue *func = emit_iftableitem(lvalue);

    for (auto expr = elist_r->rbegin(); expr != elist_r->rend(); ++expr) {
        emit(param_iop, *expr, nullptr, nullptr);
    }

    emit(call_iop, func, nullptr, nullptr);

    exprValue *result = new exprValue(varExpr_T);

    result->setSymbol(newTempvar());
    emit(get_retval_iop, result, nullptr, nullptr);

    return result;
}

static exprValue *member_item(exprValue *lvalue, std::string name) {
    lvalue = emit_iftableitem(lvalue);

    exprValue *tableitem = new exprValue(TableitemExpr_T);
    tableitem->setSymbol(lvalue->getSymbol());

    tableitem->setIndex(new exprValue(name));

    return tableitem;
}

void check_arithm(exprValue *expr) {
    if (!expr->isOperand()) {
        ++comp_err;
        std::cerr << BRED "Illegal expression used in line " << yylineno << RST << std::endl;
    }
}

static exprValue *expr_op_emit(iopcode op, exprValue *expr_left, exprValue *expr_right) {
    exprValue *expr_res;

    if (expr_left->isOperand() && expr_right->isOperand()) {
        expr_res = new exprValue(arithmexprExpr_T);

        expr_res->setSymbol(newTempvar());
        emit(op, expr_res, expr_left, expr_right);
    } else {
        ++comp_err;

        std::cerr << BRED "Invalid operation between " << expr_left->to_string() << " (" << expr_left->type_string() << ") and "
                  << expr_right->to_string() << " (" << expr_right->type_string() << ") in line " << yylineno << RST << std::endl;

        expr_res = new exprValue(nilExpr_T);
    }

    return expr_res;
}

static exprValue *expr_relop_emit(iopcode relop, exprValue *expr_left, exprValue *expr_right) {
    exprValue *expr_res;

    if (expr_left->isOperand() && expr_right->isOperand()) {
        expr_res = new exprValue(boolexprExpr_T);
        expr_res->setSymbol(newTempvar());

        expr_res->setTruelist(newlist(nextQuadLabel()));
        expr_res->setFalselist(newlist(nextQuadLabel() + 1));

        emit(relop, expr_left, expr_right, 0UL);
        emit(jump_iop, nullptr, nullptr, 0UL);
    } else {
        ++comp_err;
        std::cerr << BRED "Invalid relational operation between " << expr_left->to_string() << " (" << expr_left->type_string() << ") and "
                  << expr_right->to_string() << " (" << expr_right->type_string() << ") in line " << yylineno << RST << std::endl;

        expr_res = new exprValue(nilExpr_T);
    }

    return expr_res;
}

static exprValue *expr_relop_eq_emit(iopcode relop, exprValue *expr_left, exprValue *expr_right) {
    assert(relop == if_eq_iop || relop == if_not_eq_iop);

    exprValue *expr_res = new exprValue(boolexprExpr_T);

    expr_res->setSymbol(newTempvar());

    expr_res->setTruelist(newlist(nextQuadLabel()));
    expr_res->setFalselist(newlist(nextQuadLabel() + 1));

    emit(relop, expr_left, expr_right, 0UL);
    emit(jump_iop, nullptr, nullptr, 0UL);

    return expr_res;
}

unsigned long merge_list(unsigned long l1, unsigned long l2) {
    if (!l1)
        return l2;

    else if (!l2)
        return l1;
    else {
        int i = l1;
        while (quad_vector.at(i).label)
            i = quad_vector.at(i).label;
        quad_vector.at(i).label = l2;
        return l1;
    }
}

exprValue *create_shorted_value(exprValue *expr) {
    exprValue *assignexprVal = new exprValue(assignexprExpr_T);

    assignexprVal->setSymbol(newTempvar());

    if (expr->isBoolExpr()) {
        exprValue *trueBool = new exprValue(true), *falseBool = new exprValue(false);

        patchList(expr->getTruelist(), nextQuadLabel());
        emit(assign_iop, assignexprVal, trueBool, nullptr);
        emit(jump_iop, nullptr, nullptr, nextQuadLabel() + 2);

        patchList(expr->getFalselist(), nextQuadLabel());
        emit(assign_iop, assignexprVal, falseBool, nullptr);
    } else if (expr->isConstBool()) {
        emit(assign_iop, assignexprVal, expr, nullptr);
    }
    return assignexprVal;
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
    stmtValue *stmt = new stmtValue();

    stmt->breaklist = 0;
    stmt->contlist = 0;

    if (expr->isBoolExpr() || expr->isConstBool()) {
        expr = create_shorted_value(expr);
    }

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
        ++comp_err;
        std::cerr << BRED "Cannot use return statement outside of function in line " << yylineno << RST << std::endl;
    }

    stmtValue *returnVal = new stmtValue();
    returnVal->breaklist = 0;
    returnVal->contlist = 0;
    returnVal->returnlist = newlist(nextQuadLabel());

    emit(jump_iop, nullptr, nullptr, 0UL);

    return returnVal;
}

stmtValue *Manage_stmt_break() {
    stmtValue *breakVal = new stmtValue();

    breakVal->contlist = 0;

    if (loopcounter > 0) {
        breakVal->breaklist = newlist(nextQuadLabel());
    } else {
        ++comp_err;
        std::cerr << BRED "Cannot use break statement while not a loop in line " << yylineno << RST << std::endl;
    }

    emit(jump_iop, nullptr, nullptr, 0UL);

    return breakVal;
}

stmtValue *Manage_stmt_continue() {
    stmtValue *contVal = new stmtValue();
    contVal->breaklist = 0;

    if (loopcounter > 0) {
        contVal->contlist = newlist(nextQuadLabel());
    } else {
        ++comp_err;
        std::cerr << BRED "Cannot use continue statement while not a loop in line " << yylineno << RST << std::endl;
    }

    emit(jump_iop, nullptr, nullptr, 0UL);

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

    if (exprLeft->isNumber() && exprRight->isNumber()) {
        expr_res = new exprValue(exprLeft->getNumConst() + exprRight->getNumConst());
    } else {
        expr_res = expr_op_emit(add_iop, exprLeft, exprRight);
    }

    return expr_res;
}

exprValue *Manage_expr_expr_MINUS_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *expr_res;

    if (exprLeft->isNumber() && exprRight->isNumber()) {
        expr_res = new exprValue(exprLeft->getNumConst() - exprRight->getNumConst());
    } else {
        expr_res = expr_op_emit(sub_iop, exprLeft, exprRight);
    }

    return expr_res;
}

exprValue *Manage_expr_expr_MUL_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *expr_res;

    if (exprLeft->isNumber() && exprRight->isNumber()) {
        expr_res = new exprValue(exprLeft->getNumConst() * exprRight->getNumConst());
    } else {
        expr_res = expr_op_emit(mul_iop, exprLeft, exprRight);
    }

    return expr_res;
}

exprValue *Manage_expr_expr_DIV_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *expr_res;

    if (exprLeft->isNumber() && exprRight->isNumber()) {

        if (exprRight->getNumConst() == 0) {
            ++comp_err;
            std::cerr << BBLU "Division by zero in line " << yylineno << RST << std::endl;
            expr_res = new exprValue(nilExpr_T);
        } else {
            expr_res = new exprValue(exprLeft->getNumConst() / exprRight->getNumConst());
        }
    } else {
        expr_res = expr_op_emit(div_iop, exprLeft, exprRight);
    }

    return expr_res;
}

exprValue *Manage_expr_expr_MOD_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *expr_res;

    if (exprLeft->isNumber() && exprRight->isNumber()) {
        if (static_cast<int>(exprRight->getNumConst()) == 0) {
            ++comp_err;
            std::cerr << BBLU "Modulo with zero in line " << yylineno << RST << std::endl;
            expr_res = new exprValue(nilExpr_T);
        } else {
            expr_res = new exprValue(static_cast<double>(static_cast<int>(exprLeft->getNumConst()) % static_cast<int>(exprRight->getNumConst())));
        }
    } else {
        expr_res = expr_op_emit(mod_iop, exprLeft, exprRight);
    }

    return expr_res;
}

exprValue *Manage_expr_expr_GT_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *expr_res;

    if (exprLeft->isNumber() && exprRight->isNumber()) {
        expr_res = new exprValue(exprLeft->getNumConst() > exprRight->getNumConst());
    } else {
        expr_res = expr_relop_emit(if_greater_iop, exprLeft, exprRight);
    }

    return expr_res;
}

exprValue *Manage_expr_expr_GE_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *expr_res;

    if (exprLeft->isNumber() && exprRight->isNumber()) {
        expr_res = new exprValue(exprLeft->getNumConst() >= exprRight->getNumConst());
    } else {
        expr_res = expr_relop_emit(if_greater_eq_iop, exprLeft, exprRight);
    }

    return expr_res;
}

exprValue *Manage_expr_expr_LT_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *expr_res;

    if (exprLeft->isNumber() && exprRight->isNumber()) {
        expr_res = new exprValue(exprLeft->getNumConst() < exprRight->getNumConst());
    } else {
        expr_res = expr_relop_emit(if_less_iop, exprLeft, exprRight);
    }

    return expr_res;
}

exprValue *Manage_expr_expr_LE_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *expr_res;

    if (exprLeft->isNumber() && exprRight->isNumber()) {
        expr_res = new exprValue(exprLeft->getNumConst() <= exprRight->getNumConst());
    } else {
        expr_res = expr_relop_emit(if_less_eq_iop, exprLeft, exprRight);
    }

    return expr_res;
}

exprValue *Manage_expr_expr_EQUAL_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *expr_res;

    if (exprLeft->isNumber() && exprRight->isNumber()) {
        expr_res = new exprValue(exprLeft->getNumConst() == exprRight->getNumConst());
    } else {
        expr_res = expr_relop_eq_emit(if_eq_iop, exprLeft, exprRight);
    }

    return expr_res;
}

exprValue *Manage_expr_expr_NEQUAL_expr(exprValue *exprLeft, exprValue *exprRight) {
    exprValue *expr_res;

    if (exprLeft->isNumber() && exprRight->isNumber()) {
        expr_res = new exprValue(exprLeft->getNumConst() != exprRight->getNumConst());
    } else {
        expr_res = expr_relop_eq_emit(if_not_eq_iop, exprLeft, exprRight);
    }

    return expr_res;
}

void short_left(iopcode op, exprValue *&left) {
    if (!left->isBoolExpr() && !left->isConstBool()) {
        exprValue *trueBool = new exprValue(true);

        left->setTruelist(newlist(nextQuadLabel()));
        left->setFalselist(newlist(nextQuadLabel() + 1));

        emit(if_eq_iop, left, trueBool, 0UL);
        emit(jump_iop, nullptr, nullptr, 0UL);

        if (op == and_iop)
            patchList(left->getTruelist(), nextQuadLabel());
        else if (op == or_iop)
            patchList(left->getFalselist(), nextQuadLabel());
        else {
            assert(false);
        }
    }
}

exprValue *Manage_expr_expr_AND_expr(exprValue *exprLeft, exprValue *exprRight, unsigned long &l1) {
    exprValue *expr_res;

    if (exprLeft->isCompileBool() && exprRight->isCompileBool()) {
        expr_res = new exprValue(*exprLeft && *exprRight);
    } else {
        if (!exprRight->isBoolExpr() && !exprRight->isConstBool()) {
            exprValue *trueBool = new exprValue(true);

            exprRight = expr_relop_eq_emit(if_eq_iop, exprRight, trueBool);
        }

        if (exprLeft->isBoolExpr() || exprLeft->isConstBool())
            patchList(exprLeft->getTruelist(), l1);

        expr_res = new exprValue(boolexprExpr_T);
        expr_res->setSymbol(newTempvar());

        expr_res->setTruelist(exprRight->getTruelist());
        expr_res->setFalselist(merge_list(exprLeft->getFalselist(), exprRight->getFalselist()));
    }

    return expr_res;
}

exprValue *Manage_expr_expr_OR_expr(exprValue *exprLeft, exprValue *exprRight, unsigned long &l1) {
    exprValue *expr_res;

    if (exprLeft->isCompileBool() && exprRight->isCompileBool()) {
        expr_res = new exprValue(*exprLeft || *exprRight);
    } else {
        if (!exprRight->isBoolExpr() && !exprRight->isConstBool()) {
            exprValue *trueBool = new exprValue(true);

            exprRight = expr_relop_eq_emit(if_eq_iop, exprRight, trueBool);
        }

        if (exprLeft->isBoolExpr() || exprLeft->isConstBool())
            patchList(exprLeft->getFalselist(), l1);

        expr_res = new exprValue(boolexprExpr_T);
        expr_res->setSymbol(newTempvar());

        expr_res->setTruelist(merge_list(exprLeft->getTruelist(), exprRight->getTruelist()));
        expr_res->setFalselist(exprRight->getFalselist());
    }

    return expr_res;
}

exprValue *Manage_expr_term(exprValue *term) {
    if (term->isBoolExpr() || term->isConstBool()) {
        term = create_shorted_value(term);
    }

    return term;
}

/* Terms */
exprValue *Manage_term_LPexprRP(exprValue *expr) {
    if (expr->isBoolExpr() || expr->isConstBool()) {
        expr = create_shorted_value(expr);
    }

    return expr;
}

exprValue *Manage_term_notexpr(exprValue *expr) {
    exprValue *termVal;

    if (!expr->isBoolExpr() && !expr->isConstBool()) {
        exprValue *trueBool = new exprValue(true);

        expr = expr_relop_eq_emit(if_eq_iop, expr, trueBool);
    }

    termVal = new exprValue(boolexprExpr_T);
    termVal->setSymbol(newTempvar());

    termVal->setFalselist(expr->getTruelist());
    termVal->setTruelist(expr->getFalselist());

    return termVal;
}

exprValue *Manage_term_PPlval(exprValue *lvalue) {
    exprValue *termVal;

    if (lvalue->isTableitem()) {
        if (lvalue->getSymbol()->type == USER_FUNC ||
            lvalue->getSymbol()->type == LIB_FUNC) {
            ++comp_err;
            std::cerr << BRED "Invalid preincrement of "
                      << lvalue->getSymbol()->type_string()
                      << " \"" << lvalue->getSymbol()->name
                      << "\" in line " << yylineno << "." RST << std::endl;
        }
    }

    check_arithm(lvalue);

    exprValue *const_num = new exprValue(1.0);

    if (lvalue->isTableitem()) {
        termVal = emit_iftableitem(lvalue);
        emit(add_iop, termVal, termVal, const_num);
        emit(table_setelem_iop, termVal, lvalue, lvalue->getIndex());
    } else {
        emit(add_iop, lvalue, lvalue, const_num);
        termVal = new exprValue(arithmexprExpr_T);

        termVal->setSymbol(newTempvar());
        emit(assign_iop, termVal, lvalue, nullptr);
    }

    return termVal;
}

exprValue *Manage_term_lvaluePP(exprValue *lvalue) {
    exprValue *termVal;

    if (lvalue->isTableitem()) {
        if (lvalue->getSymbol()->type == USER_FUNC ||
            lvalue->getSymbol()->type == LIB_FUNC) {
            ++comp_err;
            std::cerr << BRED "Invalid postincrement of "
                      << lvalue->getSymbol()->type_string()
                      << " \"" << lvalue->getSymbol()->name
                      << "\" in line " << yylineno << "." RST << std::endl;
        }
    }

    check_arithm(lvalue);
    termVal = new exprValue(varExpr_T);

    termVal->setSymbol(newTempvar());

    exprValue *const_num = new exprValue(1.0);

    if (lvalue->isTableitem()) {
        exprValue *val = emit_iftableitem(lvalue);

        emit(assign_iop, termVal, val, nullptr);
        emit(add_iop, val, val, const_num);
        emit(table_setelem_iop, val, lvalue, lvalue->getIndex());
    } else {
        emit(assign_iop, termVal, lvalue, nullptr);
        emit(add_iop, lvalue, lvalue, const_num);
    }

    return termVal;
}

exprValue *Manage_term_MMlval(exprValue *lvalue) {
    exprValue *termVal;

    if (lvalue->isTableitem()) {
        if (lvalue->getSymbol()->type == USER_FUNC ||
            lvalue->getSymbol()->type == LIB_FUNC) {
            ++comp_err;
            std::cerr << BRED "Invalid predecrement of "
                      << lvalue->getSymbol()->type_string()
                      << " \"" << lvalue->getSymbol()->name
                      << "\" in line " << yylineno << "." RST << std::endl;
        }
    }

    check_arithm(lvalue);

    exprValue *const_num = new exprValue(1.0);

    if (lvalue->isTableitem()) {
        termVal = emit_iftableitem(lvalue);
        emit(sub_iop, termVal, termVal, const_num);
        emit(table_setelem_iop, termVal, lvalue, lvalue->getIndex());
    } else {
        emit(sub_iop, lvalue, lvalue, const_num);
        termVal = new exprValue(arithmexprExpr_T);

        termVal->setSymbol(newTempvar());
        emit(assign_iop, termVal, lvalue, nullptr);
    }

    return termVal;
}

exprValue *Manage_term_lvalueMM(exprValue *lvalue) {
    exprValue *termVal;

    if (lvalue->isTableitem()) {
        if (lvalue->getSymbol()->type == USER_FUNC ||
            lvalue->getSymbol()->type == LIB_FUNC) {
            ++comp_err;
            std::cerr << BRED "Invalid postdecrement of "
                      << lvalue->getSymbol()->type_string()
                      << " \"" << lvalue->getSymbol()->name
                      << "\" in line " << yylineno << "." RST << std::endl;
        }
    }

    check_arithm(lvalue);
    termVal = new exprValue(varExpr_T);

    termVal->setSymbol(newTempvar());

    exprValue *const_num = new exprValue(1.0);

    if (lvalue->isTableitem()) {
        exprValue *val = emit_iftableitem(lvalue);

        emit(assign_iop, termVal, val, nullptr);
        emit(sub_iop, val, val, const_num);
        emit(table_setelem_iop, val, lvalue, lvalue->getIndex());
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
    exprValue *termVal = new exprValue(arithmexprExpr_T);

    check_arithm(expr);

    termVal->setSymbol(newTempvar());
    emit(mul_iop, termVal, new exprValue(-1.0), expr);

    return termVal;
}

/* Assign expression */
exprValue *Manage_assignexpr_lvalueASSIGNexpr(exprValue *lvalue, exprValue *expr) {
    exprValue *assignexprVal;

    if (lvalue->isVariable()) {
        Symbol *symbol = lvalue->getSymbol();

        if (funcDepth != symbol->funcDepth &&
            dynamic_cast<Variable *>(symbol)->scope != 0) {
            ++comp_err;
            std::cerr << BRED "Inaccessible " << symbol->type_string() << " \"" << symbol->name << "\" in line " << yylineno << RST << std::endl;

            assignexprVal = new exprValue(nilExpr_T);
        } else {
            if (expr->isBoolExpr() || expr->isConstBool()) {
                expr = create_shorted_value(expr);
            }

            emit(assign_iop, lvalue, expr, nullptr);

            assignexprVal = new exprValue(assignexprExpr_T);

            assignexprVal->setSymbol(newTempvar());
            emit(assign_iop, assignexprVal, lvalue, nullptr);
        }
    } else if (lvalue->isTableitem()) {
        if (expr->isBoolExpr() || expr->isConstBool()) {
            expr = create_shorted_value(expr);
        }

        emit(table_setelem_iop, expr, lvalue, lvalue->getIndex());

        assignexprVal = emit_iftableitem(lvalue, true);
    } else {
        ++comp_err;
        std::cerr << BRED "Cannot assign to " << lvalue->type_string() << " \"" << lvalue->to_string() << "\" in line " << yylineno << "." RST << std::endl;

        assignexprVal = new exprValue(nilExpr_T);
    }

    return assignexprVal;
}

/* Primary */
exprValue *Manage_primary_lvalue(exprValue *lvalue) {
    exprValue *primaryValueVal = lvalue;

    if (!lvalue->isNil()) {

        Symbol *symbol = lvalue->getSymbol();
        if (symbol->scope == 0 ||
            symbol->type == USER_FUNC ||
            symbol->type == LIB_FUNC ||
            funcDepth == symbol->funcDepth) {

            primaryValueVal = emit_iftableitem(lvalue);
        } else {
            ++comp_err;
            std::cerr << BRED "Inaccessible " << symbol->type_string() << " \"" << symbol->name << "\" in line " << yylineno << RST << std::endl;
            delete lvalue;
            primaryValueVal = new exprValue(nilExpr_T);
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
    exprValue *primaryVal = new exprValue(userfuncExpr_T);
    primaryVal->setSymbol(funcdef);

    return primaryVal;
}

exprValue *Manage_primary_const(exprValue *constVal) {
    return constVal;
}

/* lvalue */
static exprValue *lvalue_expr(Symbol *symbol) {
    assert(symbol);

    exprValue *e;

    switch (symbol->type) {
    case VARIABLE:
        e = new exprValue(varExpr_T);
        break;

    case USER_FUNC:
        e = new exprValue(userfuncExpr_T);
        break;

    case LIB_FUNC:
        e = new exprValue(libfuncExpr_T);
        break;

    default:
        assert(false);
    }

    e->setSymbol(symbol);

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
            ++comp_err;
            std::cerr << BRED "Variable \"" << id << "\" in line " << yylineno
                      << " attempts to shadow library function." RST << std::endl;

            newStructVal = new exprValue(nilExpr_T);
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
        ++comp_err;
        std::cerr << BRED "Undefined reference to global symbol \"" << id << "\" in line " << yylineno << "." RST << std::endl;

        newStructVal = new exprValue(nilExpr_T);
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

    tableitem = new exprValue(TableitemExpr_T);
    tableitem->setSymbol(lvalue->getSymbol());

    if (expr->isBoolExpr() || expr->isConstBool()) {
        expr = create_shorted_value(expr);
    }

    tableitem->setIndex(expr);

    return tableitem;
}

exprValue *Manage_member_callDOTid(exprValue *call, std::string id) {
    return member_item(call, id);
}

exprValue *Manage_member_callLSBexprRSB(exprValue *call, exprValue *expr) {
    exprValue *tableitem;

    call = emit_iftableitem(call);

    tableitem = new exprValue(TableitemExpr_T);
    tableitem->setSymbol(call->getSymbol());

    if (expr->isBoolExpr() || expr->isConstBool()) {
        expr = create_shorted_value(expr);
    }

    tableitem->setIndex(expr);

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
    exprValue *func = new exprValue(userfuncExpr_T);
    func->setSymbol(funcdef);

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
    if (expr->isBoolExpr() || expr->isConstBool()) {
        expr = create_shorted_value(expr);
    }

    list->push_back(expr);
}

void Manage_exprOptRpt_expr(exprValue *expr, exprList &list) {
    list = new std::list<exprValue *>();

    if (expr->isBoolExpr() || expr->isConstBool()) {
        expr = create_shorted_value(expr);
    }

    list->push_back(expr);
}

/* Objectdef */
exprValue *Manage_objectdef_LSBelistRSB(exprList elist) {
    exprValue *objdefVal = new exprValue(newtableExpr_T);

    objdefVal->setSymbol(newTempvar());
    emit(table_create_iop, objdefVal, nullptr, nullptr);

    unsigned long i = 0;
    for (auto &expr : *elist) {
        exprValue *constVal = new exprValue(static_cast<double>(i++));

        emit(table_setelem_iop, expr, objdefVal, constVal);
    }

    return objdefVal;
}

exprValue *Manage_objectdef_LSBindexedRSB(indexedList indexed) {
    exprValue *objdefVal = new exprValue(newtableExpr_T);

    objdefVal->setSymbol(newTempvar());
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

    if (value->isBoolExpr() || value->isConstBool()) {
        value = create_shorted_value(value);
    }

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
        ++comp_err;
        std::cerr << BRED "Cannot define function \"" << funcName << "\" in line " << yylineno
                  << ". It would shadow a library function." RST << std::endl;

        return nullptr;
    }

    auto symbol_in_table = symbolTableObj.lookup_scope(funcName, scopeLevel);

    if (symbol_in_table != nullptr) {
        ++comp_err;
        std::cerr << BRED "Cannot define function \"" << funcName
                  << "\" in line " << yylineno << ". It shadows previous "
                  << symbol_in_table->type_string() << " defined in line "
                  << symbol_in_table->line << "." RST << std::endl;

        return nullptr;
    }

    emit(jump_iop, nullptr, nullptr, 0UL);

    newFunc = new Function(funcName, scopeLevel, yylineno, funcDepth, USER_FUNC, currScopespaceOffset(), nextQuadLabel());

    symbolTableObj.insert(funcName, newFunc, scopeLevel);

    exprValue *funcprefix = new exprValue(userfuncExpr_T);
    funcprefix->setSymbol(newFunc);

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
        auto symbol_in_table = symbolTableObj.lookup_scope(id->getStrConst(), scopeLevel);

        if (argSet.count(id->getStrConst()) > 0) {
            ++comp_err;
            std::cerr << BRED "Duplicate argument \"" << id->getStrConst() << "\" in line " << yylineno << RST << std::endl;

            return false;
        } else if (isLibFunction(id->getStrConst())) {
            ++comp_err;
            std::cerr << BRED "Formal argument \"" << id->getStrConst() << "\" in line " << yylineno
                      << " attempts to shadow a library function." RST << std::endl;

            return false;
        } else if (symbol_in_table != nullptr) {
            std::cerr << BRED "Formal argument \"" << id->getStrConst() << "\" in line "
                      << yylineno << " attempts to shadow with previous "
                      << symbol_in_table->type_string() << " defined in line "
                      << symbol_in_table->line << "." RST << std::endl;

            return false;
        }

        argSet.insert(id->getStrConst());
    }

    return true;
}

void Manage_funcargs(exprList &idlist) {
    ++scopeLevel;

    if (check_funcargs(idlist)) {
        for (auto &id : *idlist) {
            Symbol *newArg = new Variable(id->getStrConst(), scopeLevel, yylineno, funcDepth, currScopespace(), currScopespaceOffset());
            symbolTableObj.insert(newArg->name, newArg, scopeLevel);

            increaseCurrScopeOffset();
        }
    }

    enterScopespace();
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

        exprValue *fpre_expr = new exprValue(userfuncExpr_T);
        fpre_expr->setSymbol(funcprefix);

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
    return new exprValue(static_cast<double>(intVal));
}

exprValue *Manage_const_real(double doubleVal) {
    return new exprValue(doubleVal);
}

exprValue *Manage_const_string(std::string strVal) {
    return new exprValue(strVal);
}

exprValue *Manage_const_nil() {
    return new exprValue(nilExpr_T);
}

exprValue *Manage_const_true() {
    return new exprValue(true);
}

exprValue *Manage_const_false() {
    return new exprValue(false);
}

/* ID list */
void Manage_idlist_ID(std::string id, exprList &list) {
    list = new std::list<exprValue *>();

    exprValue *id_expr = new exprValue(id);

    list->push_back(id_expr);
}

void Manage_idlist_idlist_comma_id(std::string id, exprList &list) {
    exprValue *id_expr = new exprValue(id);

    list->push_back(id_expr);
}

void Manage_idlist(exprList &list) {
    list = new std::list<exprValue *>();
}

/* If statement */
unsigned long Manage_ifprefix(exprValue *expr) {
    exprValue *constboolVal = new exprValue(true);

    if (expr->isBoolExpr() || expr->isConstBool()) {
        expr = create_shorted_value(expr);
    }

    emit(if_eq_iop, expr, constboolVal, nextQuadLabel() + 2);

    unsigned long tmp_nextquad = nextQuadLabel();

    emit(jump_iop, nullptr, nullptr, 0UL);

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

    emit(jump_iop, nullptr, nullptr, 0UL);

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
    exprValue *constbool = new exprValue(true);

    if (expr->isBoolExpr() || expr->isConstBool()) {
        expr = create_shorted_value(expr);
    }

    emit(if_eq_iop, expr, constbool, nextQuadLabel() + 2);

    unsigned long whilecond = nextQuadLabel();

    emit(jump_iop, nullptr, nullptr, 0UL);

    return whilecond;
}

stmtValue *Manage_while(unsigned long whilestart, unsigned long whilecond, stmtValue *stmt) {
    emit(jump_iop, nullptr, nullptr, whilestart);
    patchLabel(whilecond, nextQuadLabel());
    patchList(stmt->breaklist, nextQuadLabel());
    patchList(stmt->contlist, whilestart);

    return stmt;
}

/* For statement */
unsigned long Manage_n() {
    unsigned long nextquad = nextQuadLabel();

    emit(jump_iop, nullptr, nullptr, 0UL);

    return nextquad;
}

unsigned long Manage_m() {
    return nextQuadLabel();
}

forprefixValue *Manage_forprefix(unsigned long m, exprValue *expr) {
    forprefixValue *forprefix = new forprefixValue();

    if (expr->isBoolExpr() || expr->isConstBool()) {
        expr = create_shorted_value(expr);
    }

    forprefix->test = m;
    forprefix->enter = nextQuadLabel();

    exprValue *constbool = new exprValue(true);

    emit(if_eq_iop, expr, constbool, 0UL);

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
    if (expr->isBoolExpr() || expr->isConstBool()) {
        expr = create_shorted_value(expr);
    }

    emit(ret_iop, expr, nullptr, nullptr);
}

void Manage_ret() {
    emit(ret_iop, nullptr, nullptr, nullptr);
}