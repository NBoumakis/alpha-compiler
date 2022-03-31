#include <string>

enum programType {
    STMT,
    PROGRAM,
    VOID
};

struct programValue {
    union value {
        struct stmtValue *stmtVal;
        struct programValue *programVal;
    };

    programType valType;
};