#ifndef __TYPES_H
#define __TYPES_H

#include <string>

enum programType {
    StmtListPr_T
};

struct programValue {
    union value {
        struct stmtListValue *stmtListVal;
    };

    programType valType;
};

enum stmtListType {
    StmtListStmtStmtL_T,
    EmptyStmtL_T
};
struct stmtListValue {
    union value {
        struct stmtList_Stmt {
            stmtListValue *stmtListVal;
            stmtValue *stmtVal;
        };
    };

    stmtListType valType;
};

enum stmtType {
    ExprStmt_T,
    IfstmtStmt_T,
    WhilestmtStmt_T,
    ForstmtStmt_T,
    ReturnstmtStmt_T,
    BreakStmt_T,
    ContiueStmt_T,
    BlockStmt_T,
    FuncdefStmt_T,
    SemicolonStmt_T
};

struct stmtValue {
    union value {
        struct exprValue *exprVal;
        struct ifstmtValue *ifstmtVal;
        struct whilestmtValue *whilestmtVal;
        struct forstmtValue *forstmtVal;
        struct returnstmtValue *returnstmtVal;
        struct blockValue *blockVal;
        struct funcdefValue *funcdefVal;
    };

    stmtType valType;
};

enum exprType {
    AssignexprExpr_T,
    ExprOpExprExpr_T,
    TermExpr_T
};

enum opType {
    PlusOp_T,
    MinusOp_T,
    MulOp_T,
    DivOp_T,
    ModOp_T,
    GTOp_T,
    GEOp_T,
    LTOp_T,
    LEOp_T,
    EqualOp_T,
    NEqualOp_T,
    AndOp_T,
    OrOp_T
};

struct exprValue {
    union value {
        struct assignexprValue *assignexprVal;
        struct exprOPValue {
            struct exprValue *exprLeftVal;
            struct exprValue *exprRightVal;
        };
        struct termValue *termVal;
    };

    exprType valType;
    opType opType;
};

enum termType {
    ExprTerm_T,
    LvalueTerm_T,
    PrimaryTerm_T
};

enum exprOpType {
    ParenthesizedExprOp_T,
    NotExprOp_T,
    UMinusExprOp_T
};

enum lvalueOpType {
    PreIncLvalueOp_T,
    PostIncLvalueOp_T,

    PreDecLvalueOp_T,
    PostDecLvalueOp_T,
};

struct termValue {
    union value {
        struct exprValue *exprVal;
        struct lvalueValue *lvalueVal;
        struct primaryValue *primaryVal;
    };

    termType valType;
    exprOpType exprType;
    lvalueOpType lvalType;
};

struct assignexprValue {
    struct lvalueValue *lvalueVal;
    struct exprValue *exprVal;
};

enum primaryType {
    lvaluePrim_T,
    callPrim_T,
    objdefPrim_T,
    funcdefPrim_T,
    constPrim_T
};

struct primaryValue {
    union value {
        struct lvalueValue *lvalueVal;
        struct callValue *callVal;
        struct objectdefValue *objectdefVal;
        struct funcdefValue *funcdefVal;
        struct constValue *constVal;
    };

    primaryType valType;
};

enum lvalueType {
    IDLvalue_T,
    MemberLvalue_T
};

struct lvalueValue {
    union value {
        std::string strVal;
        struct memberValue *memberVal;
    };

    lvalueType valType;
};

enum memberType {
    lvalue_IDMember_T,
    lvalue_exprMember_T,
    call_IDMember_T,
    call_exprMember_T
};

struct memberValue {
    union value {
        struct memberLvalueIDValue {
            struct lvalueValue *lvalueVal;
            std::string id;
        };
        struct memberLvalueExprValue {
            struct lvalueValue *lvalueVal;
            struct exprValue *exprVal;
        };
        struct memberCallIDValue {
            struct callValue *callVal;
            std::string id;
        };
        struct memberCallExprValue {
            struct callValue *callVal;
            struct exprValue *exprVal;
        };
    };

    memberType valTypes;
};

enum callType {
    callElistCall_T,
    lvalueCallSuffCall_T,
    funcdefElistCall_T
};

struct callValue {
    union value {
        struct callCallElistValue {
            struct callValue *callVal;
            struct elistValue *elistVal;
        };
        struct callLvalueValue {
            struct lvalueValue *lvalueVal;
            struct callsuffixValue *callsuffixVal;
        };
        struct callFuncdefValue {
            struct funcdefValue *funcdefVal;
            struct elistValue *elistVal;
        };
    };

    callType valType;
};

enum callsuffixType {
    normcallCallsuff_T,
    methodcallCallsuff_T
};

struct callsuffixValue {
    union value {
        struct normcallValue *normcallVal;
        struct methodcallValue *methodcallVal;
    };
};

struct normcallValue {
    union value {
        struct elistValue *elistVal;
    };
};

struct methodcallValue {
    union value {
        struct {
            std::string idVal;
            struct elistValue *elistVal;
        };
    };
};

enum elistType {
    exprOptRptElist_T,
    emptyElist_T
};

struct elistValue {
    union value {
        struct exprOptRptValue *exprOptRptVal;
    };

    elistType valType;
};

enum exprOptRptType {
    exprExprOptRpt_T,
    exprORExprOptRpt_T
};

struct exprOptRptValue {
    union value {
        struct exprOptRptExprValue {
            struct exprOptRptValue *exprOptRptVal;
            struct exprValue *exprVal;
        };

        struct exprValue *exprVal;
    };

    exprOptRptType valType;
};

enum objectdefType {
    elistObjdef_T,
    indexedObjdef_T
};

struct objectdefValue {
    union value {
        struct elistValue *elistVal;
        struct indexedValue *indexedVal;
    };

    objectdefType valType;
};

enum indexedType {
    indelemIndexed_T,
    VOID_Indexed_T
};

struct indexedValue {
    union value {
        struct indelemlistValue *indelemlistVal;
    };

    indexedType valType;
};

enum indelemlistType {
    indexedelem_IndelemlistIndeleml_T,
    indexedelemIndeleml_T
};

struct indelemlistValue {
    union value {
        struct indelemIndexedelemlistValue {
            struct indexedelemValue *indexedelemVal;
            struct indelemlistValue *indelemlistVal;
        };
        struct indexedelemlistValue {
            struct indexedelemValue *indexedelemVal;
        };
    };

    indelemlistType valType;
};

enum indexedelemType {
    exprExprIndexedelem_T
};

struct indexedelemValue {
    union value {

        struct indexedelemExprValue {
            struct exprValue *keyExprVal;
            struct exprValue *valueExprVal;
        };
    };

    indexedelemType valType;
};

enum blockType {
    stmtListBlock_T
};

struct blockValue {
    union value {
        struct stmtListValue *stmtListVal;
    };

    blockType valType;
};

enum funcdefType {
    ID,
    IDLIST,
    BLOCK
};

struct funcdefValue {
    union value {
        struct funcdefIDValue {
            std::string strVal;
            struct idlistValue *idlistVal;
            struct blockValue *blockVal;
        };
        struct funcdefNOIDValue {
            struct idlistValue *idlistVal;
            struct blockValue *blockVal;
        };
    };

    funcdefType valType;
};

enum constTypes {
    INT,
    DOUBLE,
    STRING,
    NIL,
    BOOL
};

struct constValue {
    union value {
        int intVal;
        double doubleVal;
        std::string stringVal;
        bool boolVal;
    };

    constTypes valType;
};

enum idlistType {
    id,
    VOID
};

struct idlistValue {
    union value {
        struct idValue *idVal;
    };

    idlistType valType;
};

enum idType {
    ID,
    VOID
};

struct idValue {
    union value {
        struct idCOMMAValue {
            std::string strVal;
            struct idValue *idVal;
        };
        struct idIDValue {
            std::string strVal;
        };
    };

    idType valType;
};

enum ifstmtType {
    EXPR,
    STMT,
    ELSE
};

struct ifstmtValue {
    union value {
        struct exprValue *valType;
        struct stmtValue *stmtVal;
        struct elseValue *elseVal;
    };

    ifstmtType valType;
};

enum elseType {
    STMT,
    VOID
};

struct elseValue {
    union value {
        struct stmtValue *stmtVal;
    };

    elseType valType;
};

enum whilestmtType {
    EXPR,
    STMT
};

struct whilestmtValue {
    union value {
        struct exprValue *exprVal;
        struct stmtValue *stmtVal;
    };

    whilestmtType valType;
};

enum forstmtType {
    ELIST,
    EXPR,
    STMT
};

struct forstmtValue {
    union Value {
        struct elistValue *elistVal;
        struct exprValue *exprVal;
        struct stmtValue *stmtVal;
    };

    forstmtType valType;
};

enum returnstmtType {
    RET
};

struct returnstmtValue {
    union value {
        struct retValue *retVal;
    };

    returnstmtType valType;
};

enum retType {
    EXPR,
    VOID
};

struct retValue {
    union value {
        struct exprValue *exprVal;
    };

    retType valType;
};

#endif /* __TYPES_H */