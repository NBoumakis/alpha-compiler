#include "vmarg.h"
#include "const_pool.h"
#include <cassert>

vmarg::vmarg(const exprValue *arg) {
    assert(arg);

    if (arg->isVariable() ||
        arg->isTableitem() ||
        arg->isArithmExpr() ||
        arg->isBoolExpr() ||
        arg->isNewtable()) {
        Variable *var_value = dynamic_cast<Variable *>(arg->getSymbol());
        assert(var_value);

        this->val = var_value->offset;

        switch (var_value->space) {
        case GLOBAL_VAR:
            this->type = global_var;
            break;

        case LOCAL_VAR:
            this->type = local_var;
            break;
        case FORMAL_ARG:
            this->type = formal_arg;
            break;
        default:
            assert(false);
        }
    } else if (arg->isConstBool()) {

        this->val = arg->getBoolConst();
        this->type = const_bool;
    } else if (arg->isConstStr()) {
        this->val = const_newstring(arg->getStrConst());
        this->type = const_str;
    } else if (arg->isNumber()) {
        this->val = const_newnumber(arg->getNumConst());
        this->type = const_num;
    } else if (arg->isNil()) {
        this->type = const_nil;
    } else if (arg->isUserfunc()) {
        this->type = user_func;
        this->val = dynamic_cast<Function *>(arg->getSymbol())->iaddress;
    } else if (arg->isLibfunc()) {
        this->type = lib_func;
        this->val = libfunc_newused(arg->getSymbol()->name);
    } else {
        assert(false);
    }
}
