#ifndef __VMARGS_H
#define __VMARGS_H

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

struct vmarg {
    vmarg_t type;
    unsigned val;
};

#endif /* __VMARGS_H */