#ifndef __TYPES_H
#define __TYPES_H

#include <string>

enum programType {
    stmtListPr_T
};

struct programValue {
    union value {
        stmtListValue *stmtListVal;
    };

    programType valType;
};

enum stmtListType {
    stmtListStmtStmtL_T,
    emptyStmtL_T
};
struct stmtListValue {
    union value {
        struct {
            stmtListValue *stmtListVal;
            stmtValue *stmtVal;
        } stmtList_Stmt;
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
        exprValue *exprVal;
        ifstmtValue *ifstmtVal;
        whilestmtValue *whilestmtVal;
        forstmtValue *forstmtVal;
        returnstmtValue *returnstmtVal;
        blockValue *blockVal;
        funcdefValue *funcdefVal;
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
        assignexprValue *assignexprVal;
        struct {
            exprValue *exprLeftVal;
            exprValue *exprRightVal;
        } exprOPValue;
        termValue *termVal;
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
        exprValue *exprVal;
        lvalueValue *lvalueVal;
        primaryValue *primaryVal;
    };

    termType valType;
    exprOpType exprType;
    lvalueOpType lvalType;
};

struct assignexprValue {
    lvalueValue *lvalueVal;
    exprValue *exprVal;
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
        lvalueValue *lvalueVal;
        callValue *callVal;
        objectdefValue *objectdefVal;
        funcdefValue *funcdefVal;
        constValue *constVal;
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
        memberValue *memberVal;
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
    };

    callType valType;
};

enum callsuffixType {
    normcallCallsuff_T,
    methodcallCallsuff_T
};

struct callsuffixValue {
    union value {
        normcallValue *normcallVal;
        methodcallValue *methodcallVal;
    };
};

struct normcallValue {
    union value {
        elistValue *elistVal;
    };
};

struct methodcallValue {
    union value {
        struct {
            std::string idVal;
            elistValue *elistVal;
        } methodIDValue;
    };
};

enum elistType {
    exprOptRptElist_T,
    emptyElist_T
};

struct elistValue {
    union value {
        exprOptRptValue *exprOptRptVal;
    };

    elistType valType;
};

enum exprOptRptType {
    exprExprOptRpt_T,
    exprORExprOptRpt_T
};

struct exprOptRptValue {
    union value {
        struct {
            exprOptRptValue *exprOptRptVal;
            exprValue *exprVal;
        } exprOptRptExprValue;

        exprValue *exprVal;
    };

    exprOptRptType valType;
};

enum objectdefType {
    elistObjdef_T,
    indexedObjdef_T
};

struct objectdefValue {
    union value {
        elistValue *elistVal;
        indexedValue *indexedVal;
    };

    objectdefType valType;
};

enum indexedType {
    indelemIndexed_T,
    VOID_Indexed_T
};

struct indexedValue {
    union value {
        indelemlistValue *indelemlistVal;
    };

    indexedType valType;
};

enum indelemlistType {
    indexedelem_IndelemlistIndeleml_T,
    indexedelemIndeleml_T
};

struct indelemlistValue {
    union value {
        struct {
            indexedelemValue *indexedelemVal;
            indelemlistValue *indelemlistVal;
        } indelemIndexedelemlistValue;
        struct {
            indexedelemValue *indexedelemVal;
        } indexedelemlistValue;
    };

    indelemlistType valType;
};

enum indexedelemType {
    exprExprIndexedelem_T
};

struct indexedelemValue {
    union value {
        struct {
            exprValue *keyExprVal;
            exprValue *valueExprVal;
        } indexedelemExprValue;
    };

    indexedelemType valType;
};

enum blockType {
    stmtListBlock_T
};

struct blockValue {
    union value {
        stmtListValue *stmtListVal;
    };

    blockType valType;
};

enum funcdefType {
    namedFuncdef_T,
    unnamedFuncdef_T
};

struct funcdefValue {
    union value {
        struct {
            std::string strVal;
            idlistValue *idlistVal;
            blockValue *blockVal;
        } funcdefIDValue;
        struct {
            idlistValue *idlistVal;
            blockValue *blockVal;
        } funcdefNOIDValue;
    };

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
    union value {
        int intVal;
        double doubleVal;
        std::string stringVal;
    };

    constTypes valType;
};

enum idlistType {
    idIdlist_T,
    idlistIdIdlist_T,
    emptyIdlist_T
};

struct idlistValue {
    union value {
        std::string id;
        struct {
            idlistValue *idlistVal;
            std::string idVal;
        } idlistIdValue;

        idlistType valType;
    };
};

enum ifstmtType {
    ifstmtIfstmt_T
};

struct ifstmtValue {
    union value {
        struct {
            exprValue *exprVal;
            stmtValue *stmtVal;
            elseValue *elseVal;
        } ifValue;
    };

    ifstmtType valType;
};

enum elseType {
    stmtElse_T,
    emptyElse_T
};

struct elseValue {
    union value {
        stmtValue *stmtVal;
    };

    elseType valType;
};

enum whilestmtType {
    exprStmtWhilestmt_T
};

struct whilestmtValue {
    union value {
        struct {
            exprValue *exprVal;
            stmtValue *stmtVal;
        } whileValue;
    };

    whilestmtType valType;
};

enum forstmtType {
    forstmtForstmt_T
};

struct forstmtValue {
    union Value {
        struct {
            elistValue *elistFirstVal;
            exprValue *exprVal;
            elistValue *elistLastVal;
            stmtValue *stmtVal;
        } elistExprStmt;
    };

    forstmtType valType;
};

enum returnstmtType {
    retReturnstmt_T
};

struct returnstmtValue {
    union value {
        retValue *retVal;
    };

    returnstmtType valType;
};

enum retType {
    exprRet_T,
    emptyRet_T
};

struct retValue {
    union value {
        exprValue *exprVal;
    };

    retType valType;
};

#endif /* __TYPES_H */