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

enum stmtType {
    EXPR,
    IFSTMT,
    WHILESTMT,
    FORSTMT,
    RETURNSTMT,
    BLOCK,
    FUNCDEF,
    VOID
};

struct stmtValue {
    union value {
        struct exprValue *exprVal;
        struct ifstmtValue *ifstmtVal;
        struct whilestmtValue *whilestmtVal;
        struct forstmtValue *forstmtVal;
        struct returnstmtValue *returnstmtVal;
        std::string BREAK;
        std::string CONTINUE;
        struct blockValue *blockVal;
        struct funcdefValue *funcdefVal;
    };

    stmtType valType;
};

enum exprType {
    ASSIGNEXPR,
    EXPR,
    TERM
};

struct exprValue {
    union value {
        struct assignexprValue *assignexprVal;
        struct exprOPValue {
            struct exprValue *exprVal;
            struct opValue *opVal;
        }; 
        struct termValue *termVal;
    };

    exprType valType;
};