#ifndef __TYPES_H
#define __TYPES_H

#include <string>

struct programValue;
struct stmtListValue;
struct stmtValue;
struct exprValue;
struct termValue;
struct assignexprValue;
struct primaryValue;
struct lvalueValue;
struct memberValue;
struct callValue;
struct callsuffixValue;
struct normcallValue;
struct methodcallValue;
struct elistValue;
struct exprOptRptValue;
struct objectdefValue;
struct indexedValue;
struct indelemlistValue;
struct indexedelemValue;
struct blockValue;
struct funcdefValue;
struct constValue;
struct idlistValue;
struct ifstmtValue;
struct elseValue;
struct whilestmtValue;
struct forstmtValue;
struct returnstmtValue;
struct retValue;

enum programType {
    stmtListPr_T
};

struct programValue {
    union {
        stmtListValue *stmtListVal;
    } value;

    programType valType;
};

enum stmtListType {
    stmtListStmtStmtL_T,
    emptyStmtL_T
};
struct stmtListValue {
    union {
        struct {
            stmtListValue *stmtListVal;
            stmtValue *stmtVal;
        } stmtList_Stmt;
    } value;

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
    union {
        exprValue *exprVal;
        ifstmtValue *ifstmtVal;
        whilestmtValue *whilestmtVal;
        forstmtValue *forstmtVal;
        returnstmtValue *returnstmtVal;
        blockValue *blockVal;
        funcdefValue *funcdefVal;
    } value;

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
    union {
        assignexprValue *assignexprVal;
        struct {
            exprValue *exprLeftVal;
            exprValue *exprRightVal;
        } exprOPValue;
        termValue *termVal;
    } value;

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
    union {
        exprValue *exprVal;
        lvalueValue *lvalueVal;
        primaryValue *primaryVal;
    } value;

    termType valType;
    exprOpType exprType;
    lvalueOpType lvalType;
};

struct assignexprValue {
    union {
        struct lvalExprVal {
            lvalueValue *lvalueVal;
            exprValue *exprVal;
        };
    } value;
};

enum primaryType {
    lvaluePrim_T,
    callPrim_T,
    objdefPrim_T,
    funcdefPrim_T,
    constPrim_T
};

struct primaryValue {
    union {
        lvalueValue *lvalueVal;
        callValue *callVal;
        objectdefValue *objectdefVal;
        funcdefValue *funcdefVal;
        constValue *constVal;
    } value;

    primaryType valType;
};

enum lvalueType {
    IDLvalue_T,
    MemberLvalue_T
};

struct lvalueValue {
    union {
        std::string strVal;
        memberValue *memberVal;
    } value;

    lvalueType valType;
};

enum memberType {
    lvalue_IDMember_T,
    lvalue_exprMember_T,
    call_IDMember_T,
    call_exprMember_T
};

struct memberValue {
    union {
        struct {
            lvalueValue *lvalueVal;
            std::string id;
        } memberLvalueIDValue;
        struct {
            lvalueValue *lvalueVal;
            exprValue *exprVal;
        } memberLvalueExprValue;
        struct {
            callValue *callVal;
            std::string id;
        } memberCallIDValue;
        struct {
            callValue *callVal;
            exprValue *exprVal;
        } memberCallExprValue;
    } value;

    memberType valTypes;
};

enum callType {
    callElistCall_T,
    lvalueCallSuffCall_T,
    funcdefElistCall_T
};

struct callValue {
    union {
        struct {
            callValue *callVal;
            elistValue *elistVal;
        } callCallElistValue;
        struct {
            lvalueValue *lvalueVal;
            callsuffixValue *callsuffixVal;
        } callLvalueValue;
        struct {
            funcdefValue *funcdefVal;
            elistValue *elistVal;
        } callFuncdefValue;
    } value;

    callType valType;
};

enum callsuffixType {
    normcallCallsuff_T,
    methodcallCallsuff_T
};

struct callsuffixValue {
    union {
        normcallValue *normcallVal;
        methodcallValue *methodcallVal;
    } value;
};

struct normcallValue {
    union {
        elistValue *elistVal;
    } value;
};

struct methodcallValue {
    union {
        struct {
            std::string idVal;
            elistValue *elistVal;
        } methodIDValue;
    } value;
};

enum elistType {
    exprOptRptElist_T,
    emptyElist_T
};

struct elistValue {
    union {
        exprOptRptValue *exprOptRptVal;
    } value;

    elistType valType;
};

enum exprOptRptType {
    exprExprOptRpt_T,
    exprORExprOptRpt_T
};

struct exprOptRptValue {
    union {
        struct {
            exprOptRptValue *exprOptRptVal;
            exprValue *exprVal;
        } exprOptRptExprValue;

        exprValue *exprVal;
    } value;

    exprOptRptType valType;
};

enum objectdefType {
    elistObjdef_T,
    indexedObjdef_T
};

struct objectdefValue {
    union {
        elistValue *elistVal;
        indexedValue *indexedVal;
    } value;

    objectdefType valType;
};

enum indexedType {
    indelemIndexed_T,
    VOID_Indexed_T
};

struct indexedValue {
    union {
        indelemlistValue *indelemlistVal;
    };

    indexedType valType;
} value;

enum indelemlistType {
    indexedelem_IndelemlistIndeleml_T,
    indexedelemIndeleml_T
};

struct indelemlistValue {
    union {
        struct {
            indexedelemValue *indexedelemVal;
            indelemlistValue *indelemlistVal;
        } indelemIndexedelemlistValue;
        struct {
            indexedelemValue *indexedelemVal;
        } indexedelemlistValue;
    } value;

    indelemlistType valType;
};

enum indexedelemType {
    exprExprIndexedelem_T
};

struct indexedelemValue {
    union {
        struct {
            exprValue *keyExprVal;
            exprValue *valueExprVal;
        } indexedelemExprValue;
    } value;

    indexedelemType valType;
};

enum blockType {
    stmtListBlock_T
};

struct blockValue {
    union {
        stmtListValue *stmtListVal;
    } value;

    blockType valType;
};

enum funcdefType {
    namedFuncdef_T,
    unnamedFuncdef_T
};

struct funcdefValue {
    union {
        struct {
            std::string strVal;
            idlistValue *idlistVal;
            blockValue *blockVal;
        } funcdefIDValue;
        struct {
            idlistValue *idlistVal;
            blockValue *blockVal;
        } funcdefNOIDValue;
    } value;

    funcdefType valType;
};

enum constTypes {
    intConst_T,
    doubleConst_T,
    stringConst_T,
    nilConst_T,
    trueConst_T,
    falseConst_T
};

struct constValue {
    union {
        int intVal;
        double doubleVal;
        std::string stringVal;
    } value;

    constTypes valType;
};

enum idlistType {
    idIdlist_T,
    idlistIdIdlist_T,
    emptyIdlist_T
};

struct idlistValue {
    union {
        std::string id;
        struct {
            idlistValue *idlistVal;
            std::string idVal;
        } idlistIdValue;

        idlistType valType;
    };
} value;

enum ifstmtType {
    ifstmtIfstmt_T
};

struct ifstmtValue {
    union {
        struct {
            exprValue *exprVal;
            stmtValue *stmtVal;
            elseValue *elseVal;
        } ifValue;
    } value;

    ifstmtType valType;
};

enum elseType {
    stmtElse_T,
    emptyElse_T
};

struct elseValue {
    union {
        stmtValue *stmtVal;
    } value;

    elseType valType;
};

enum whilestmtType {
    exprStmtWhilestmt_T
};

struct whilestmtValue {
    union {
        struct {
            exprValue *exprVal;
            stmtValue *stmtVal;
        } whileValue;
    } value;

    whilestmtType valType;
};

enum forstmtType {
    forstmtForstmt_T
};

struct forstmtValue {
    union {
        struct {
            elistValue *elistFirstVal;
            exprValue *exprVal;
            elistValue *elistLastVal;
            stmtValue *stmtVal;
        } elistExprStmt;
    } value;

    forstmtType valType;
};

enum returnstmtType {
    retReturnstmt_T
};

struct returnstmtValue {
    union {
        retValue *retVal;
    };

    returnstmtType valType;
} value;

enum retType {
    exprRet_T,
    emptyRet_T
};

struct retValue {
    union {
        exprValue *exprVal;
    } value;

    retType valType;
};

#endif /* __TYPES_H */