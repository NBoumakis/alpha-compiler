#ifndef __ICODE_H
#define __ICODE_H

enum iopcode {
    assign_iop,
    add_iop,
    sub_iop,
    mul_iop,
    div_iop,
    mod_iop,
    uminus_iop,
    and_iop,
    or_iop,
    not_iop,
    if_eq_iop,
    if_not_eq_iop,
    if_less_eq_iop,
    if_greater_eq_iop,
    if_less_iop,
    if_greater_iop,
    call_iop,
    param_iop,
    ret_iop,
    get_retval_iop,
    funcstart_iop,
    funcend_iop,
    table_create_iop,
    table_getelem_iop,
    table_setelem_iop
};

#endif /* __ICODE_H */