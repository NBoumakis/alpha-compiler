#ifndef __VMARGS_H
#define __VMARGS_H

#include "types.h"

enum vmarg_t { instruction_label,
               global_var,
               formal_arg,
               local_var,
               const_num,
               const_str,
               const_bool,
               const_nil,
               user_func,
               lib_func,
               dest_register };

class vmarg {
public:
    vmarg_t type;
    unsigned long val;

    vmarg(const exprValue *arg);
    vmarg(double val);
    vmarg(bool val);
    vmarg(vmarg_t type, unsigned long val);
};

#endif /* __VMARGS_H */