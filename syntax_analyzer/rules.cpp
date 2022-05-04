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
        emit(param_iop, elist_r, nullptr, nullptr);
        elist_r = elist_r->next;
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

        expr_res->valType = InvalidExpr_T;
    }

    return expr_res;
}

static exprValue *expr_relop_emit(iopcode relop, exprValue *expr_left, exprValue *expr_right) {
    exprValue *expr_res = new exprValue();

    if (valid_op_expr(expr_left) && valid_op_expr(expr_right)) {
        expr_res->valType = boolexprExpr_T;

        expr_res->symbolVal = newTempvar();

        emit(relop, expr_left, expr_right, nextQuadLabel() + 3);

        exprValue *constbool = new exprValue();
        constbool->valType = constboolExpr_T;
        constbool->boolConstVal = false;
        emit(assign_iop, expr_res, constbool);

        emit(jump_iop, nextQuadLabel() + 2);

        constbool = new exprValue();
        constbool->valType = constboolExpr_T;
        constbool->boolConstVal = true;
        emit(assign_iop, expr_res, constbool);
    } else {
        std::cerr << BRED "Invalid relational operation between " << expr_left->to_string() << " (" << expr_left->type_string() << ") and "
                  << expr_right->to_string() << " (" << expr_right->type_string() << ") in line " << yylineno << RST << std::endl;

        expr_res->valType = InvalidExpr_T;
    }

    return expr_res;
}

static exprValue *expr_boolop_emit(iopcode boolop, exprValue *expr_left, exprValue *expr_right) {
    exprValue *expr_res = new exprValue();
    expr_res->valType = boolexprExpr_T;

    expr_res->symbolVal = newTempvar();
    emit(boolop, expr_res, expr_left, expr_right);

    return expr_res;
}

programValue *Manage_program(stmtListValue *stmtList) {
    return nullptr;
}

stmtListValue *Manage_stmtList_stmt(stmtListValue *stmtList, stmtValue *stmt) {
    return nullptr;
}

stmtListValue *Manage_stmtList() {
    return nullptr;
}

/* Statements */
stmtValue *Manage_stmt_expr(exprValue *expr) {
    resettemp();
    return nullptr;
}

stmtValue *Manage_stmt_ifstmt() {
    return nullptr;
}

stmtValue *Manage_stmt_whilestmt(whilestmtValue *whilestmt) {
    return nullptr;
}

stmtValue *Manage_stmt_forstmt(forstmtValue *forstmt) {
    return nullptr;
}

stmtValue *Manage_stmt_returnstmt(returnstmtValue *returnstmt) {
    return nullptr;
}

stmtValue *Manage_stmt_break() {
    return nullptr;
}

stmtValue *Manage_stmt_continue() {
    return nullptr;
}

stmtValue *Manage_stmt_block(blockValue *block) {
    return nullptr;
}

stmtValue *Manage_stmt_funcdef(Function *funcdef) {
    return nullptr;
}

stmtValue *Manage_stmt_semicolon() {
    resettemp();

    return nullptr;
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
            expr_res->valType = InvalidExpr_T;
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
            expr_res->valType = InvalidExpr_T;
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
        expr_res->valType = boolexprExpr_T;

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
        expr_res->valType = boolexprExpr_T;

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
        expr_res->valType = boolexprExpr_T;

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
        expr_res->valType = boolexprExpr_T;

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
        expr_res->valType = boolexprExpr_T;

        expr_res->boolConstVal = (exprLeft->numConstval != exprRight->numConstval);
    } else {
        expr_res = expr_relop_emit(if_not_eq_iop, exprLeft, exprRight);
    }

    return expr_res;
}

exprValue *Manage_expr_expr_AND_expr(exprValue *exprLeft, exprValue *exprRight) {
    return expr_boolop_emit(and_iop, exprLeft, exprRight);
}

exprValue *Manage_expr_expr_OR_expr(exprValue *exprLeft, exprValue *exprRight) {
    return expr_boolop_emit(or_iop, exprLeft, exprRight);
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
    termVal->valType = boolexprExpr_T;

    termVal->symbolVal = newTempvar();

    emit(not_iop, termVal, expr, nullptr);

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
        emit(table_setelem_iop, lvalue, lvalue->indexVal, termVal);
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
        emit(table_setelem_iop, lvalue, lvalue->indexVal, val);
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
        emit(table_setelem_iop, lvalue, lvalue->indexVal, termVal);
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
        emit(table_setelem_iop, lvalue, lvalue->indexVal, val);
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
            emit(assign_iop, lvalue, expr, nullptr);

            assignexprVal = new exprValue();
            assignexprVal->valType = assignexprExpr_T;

            assignexprVal->symbolVal = newTempvar();
            emit(assign_iop, assignexprVal, lvalue, nullptr);
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

    Symbol *symbol = lvalue->symbolVal;
    if (symbol->scope == 0 ||
        symbol->type == USER_FUNC ||
        symbol->type == LIB_FUNC ||
        funcDepth == symbol->funcDepth) {

        primaryValueVal = emit_iftableitem(lvalue);
    } else {
        std::cerr << BRED "Inaccessible " << type_names[symbol->type] << " \"" << symbol->name << "\" in line " << yylineno << RST << std::endl;
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
exprValue *Manage_elist_exprOptRpt(exprValue *exprOptRpt) {
    return exprOptRpt;
}

exprValue *Manage_elist() {
    return nullptr;
}

/* Expression optional and repeatable */
exprValue *Manage_exprOptRpt_expr_exprOptRpt(exprValue *expr, exprValue *exprOptRpt) {
    expr->next = exprOptRpt;
    return expr;
}

exprValue *Manage_exprOptRpt_expr(exprValue *expr) {
    return expr;
}

/* Objectdef */
exprValue *Manage_objectdef_LSBelistRSB(exprValue *elist) {
    exprValue *objdefVal = new exprValue();
    objdefVal->valType = newtableExpr_T;

    objdefVal->symbolVal = newTempvar();
    emit(table_create_iop, objdefVal, nullptr, nullptr);

    for (int i = 0; elist; elist = elist->next) {
        exprValue *constVal = new exprValue();
        constVal->valType = constnumExpr_T;
        constVal->numConstval = i++;

        emit(table_setelem_iop, objdefVal, constVal, elist);
    }

    return objdefVal;
}

exprValue *Manage_objectdef_LSBindexedRSB(exprValue *indexed) {
    exprValue *objdefVal = new exprValue();
    objdefVal->valType = newtableExpr_T;

    objdefVal->symbolVal = newTempvar();
    emit(table_create_iop, objdefVal, nullptr, nullptr);

    for (; indexed; indexed = indexed->next) {
        emit(table_setelem_iop, objdefVal, indexed->indexVal, indexed);
    }

    return objdefVal;
}

/* Indexed */
exprValue *Manage_indexed(exprValue *indelemlist) {
    exprValue *newStructVal;
    return newStructVal;
}

/* Indexed element list */
exprValue *Manage_indelemlist(indexedelemValue *indexedelem, exprValue *indelemlist) {
    exprValue *newStructVal;
    return newStructVal;
}

exprOptRptValue *Manage_indexed_indexedelem(exprOptRptValue *indexedelem) {
    return indexedelem;
}

indexedelemValue *Manage_indexedelem_LCB_expr_COLON_expr_RCB(exprValue *key, exprValue *value) {
    indexedelemValue *newStructVal;
    return newStructVal;
}

/* Block */
blockValue *Manage_block_LCBstmtRCB(stmtListValue *stmt) {
    return nullptr;
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
    return nullptr;
}

elseValue *Manage_else() {
    return nullptr;
}

/* While statement */
whilestmtValue *Manage_whilestmt(exprValue *expr, stmtValue *stmt) {
    return nullptr;
}

/* For statement */
forstmtValue *Manage_for(exprValue *elistFirst, exprValue *expr, exprValue *elistLast, stmtValue *stmt) {
    return nullptr;
}

/* Return statement */
returnstmtValue *Manage_returnstmt(retValue *ret) {
    if (funcDepth == 0) {
        std::cerr << BRED "Cannot use return statement outside of function in line " << yylineno << RST << std::endl;
    }

    return nullptr;
}

/* Return */
retValue *Manage_ret_expr(exprValue *expr) {
    return nullptr;
}

retValue *Manage_ret() {
    return nullptr;
}