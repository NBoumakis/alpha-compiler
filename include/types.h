#ifndef __TYPES_H
#define __TYPES_H

#include <string>

enum programType {
    StmtList
};

struct programValue {
    union value {
        struct stmtListValue *stmtListVal;
    };

    programType valType;
};

enum stmtListType {
    StmtListStmt,
    Empty
};
struct stmtListValue {
    union value {
        stmtListValue *stmtListVal;
        stmtValue *stmtVal;
    };

    stmtListType valType;
};

enum stmtType {
    Expr,
    Ifstmt,
    Whilestmt,
    Forstmt,
    Returnstmt,
    Break,
    Continue,
    Block,
    Funcdef,
    Empty
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
    Assignexpr,
    ExprPlusExpr,
    ExprMinusExpr,
    ExprMulExpr,
    ExprDivExpr,
    ExprModExpr,
    ExprGtExpr,
    ExprGeExpr,
    ExprLtExpr,
    ExprLeExpr,
    ExprEqualExpr,
    ExprNequalExpr,
    ExprAndExpr,
    ExprOrExpr,
    TERM
};

struct exprValue {
    union value {
        struct assignexprValue *assignexprVal;
        struct exprPlusValue {
            struct exprValue *exprVal;
            std::string PLUS;
        };
        struct exprMinusValue {
            struct exprValue *exprVal;
            std::string MINUS;
        };
        struct exprMulValue {
            struct exprValue *exprVal;
            std::string MUL;
        };
        struct exprDivValue {
            struct exprValue *exprVal;
            std::string DIV;
        };
        struct exprModValue {
            struct exprValue *exprVal;
            std::string MOD;
        };
        struct exprGtValue {
            struct exprValue *exprVal;
            std::string GT;
        };
        struct exprGeValue {
            struct exprValue *exprVal;
            std::string GE;
        };
        struct exprLtValue {
            struct exprValue *exprVal;
            std::string LT;
        };
        struct exprLeValue {
            struct exprValue *exprVal;
            std::string LT;
        };
        struct exprEqualValue {
            struct exprValue *exprVal;
            std::string EQUAL;
        };
        struct exprNequalValue {
            struct exprValue *exprVal;
            std::string NEQUAL;
        };
        struct exprAndValue {
            struct exprValue *exprVal;
            std::string AND;
        };
        struct exprOrValue {
            struct exprValue *exprVal;
            std::string OR;
        };
        struct termValue *termVal;
    };

    exprType valType;
};

enum termType {
    LparExprRpar,
    NotExpr,
    PlusplusLvalue,
    LvaluePlusplus,
    MinusminusLvalue,
    LvalueMinusminus,
    Primary,
    MinusExpr
};

struct termValue {
    union value {
        struct termExprBracketsSValue {
            std::string L_PARENTHSESIS;
            struct exprValue *exprVal;
            std::string R_PARENTHSESIS;
        };
        struct termNotExprValue {
            std::string NOT;
            struct exprValue *exprVal;
        };
        struct termPlusplusLvalueValue {
            std::string PLUS_PLUS;
            struct lvalueValue *lvalueVal;
        };
        struct termLvaluePlusplusValue {
            struct lvalueValue *lvalueVal;
            std::string PLUS_PLUS;
        };
        struct termMinusminusLvalueValue {
            std::string MINUS_MINUS;
            struct lvalueValue *lvalueVal;
        };
        struct termLvaluemMinusminusValue {
            struct lvalueValue *lvalueVal;
            std::string MINUS_MINUS;
        };
        struct termPrimaryValue {
            struct primaryValue *primaryVal;
        };
        struct termMinusExprValue {
            std::string MINUS;
            struct exprValue *exprVal;
        };
    };

    termType valType;
};

enum assignexprType {
    LvalueExpr
};

struct assignexprValue {
    union value {
        struct assignexprLvalueExprValue{
            struct lvalueValue *lvalueVal;
            struct exprValue *exprVal;
        };
    };

    assignexprType valType;
};

enum primaryType {
    Lvalue,
    Call,
    Objectdef,
    Funcdef,
    Const
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
    Id,
    Local,
    Namespace,
    Member
};

struct lvalueValue {
    union value {
        std::string strVal;
        struct lvalueLocalIDValue {
            std::string LOCAL;
            std::string id;
        };
        struct lvalueNamespaceIDValue {
            std::string NAMESPACE;
            std::string id;
        };
        struct memberValue *memberVal;
    };

    lvalueType valType;
};

enum memberType {
    LvalueID,
    LvalueExpr,
    CallID,
    CallExpr
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
        struct memberCallEXprValue {
            struct callValue *callVal;
            struct exprValue *exprVal;
        };
    };

    memberType valTypes;
};

enum callType {
    CallElist,
    LvalueCallsuffix,
    FuncdefElist
};

struct callValue {
    union value {
        struct callElistValue {
            struct callValue *callVal;
            struct elistValue *elistVal;
        };
        struct callLvalueValue {
            struct lvalueValue *lvalueVal;
            struct callsuffixValue *callsuffixVAl;
        };
        struct callFuncdefElistValue {
            struct funcdefValue *funcdefVal;
            struct elistValue *elistVAl;
        };
    };

    callType valType;
};

enum callsuffixType {
    Normcall,
    Methodcall
};

struct callsuffixValue {
    union value {
        struct normcallValue *normcallVal;
        struct methodcallValue *methodcallVal;
    };
};

enum normcallType {
    LparElistRpar
};

struct normcallValue {
    union value {
        struct elistValue *elistVal;
    };

    normcallType valType;
};

enum methodcallType {
    IDElist
};

struct methodcallValue {
    union value {
        struct methodcallIDElistValue {
            std::string strVal;
            struct elistValue *elistVal;
        };
    };

    methodcallType valType;
};

enum elistType {
    ExprOptRpt,
    Empty
};

struct elistValue {
    union value {
        struct exprOptRptValue *exprOptRptVal;
    };

    elistType valType;
};

enum exprOptRptType {
    ExprExprOptRpt,
    Expr
};

struct exprOptRptValue {
    union value {
        struct exprOptRptExprCommaValue {
            struct exprOptRpt *exprOptRptVal;
        };
        struct exprOptRptExprValue {
            struct exprValue *exprVal;
        };
    };

    exprOptRptType valType;
};

enum objectdefType {
    LsqElistPsq,
    LsqIndexedRsq
};

struct objectdefValue {
    union value {
        struct objectdefElistValue {
            struct elistValue *elistVal;
        };
        struct objectdefIndexedValue {
            struct indexedValue *indexedVal;
        };
    };

    objectdefType valType;
};

enum indexedType {
    Indelemlist,
    Empty
};

struct indexedValue {
    union value {
        struct indelemlistValue *indelemlistVal;
    };

    indexedType valType;
};

enum indelemlistType {
    IndexedlemIndelemlist,
    Indelemlist
};

struct indelemlistValue {
    union value {
        struct indelemlistCommaValue {
            struct indexedelemValue *indexedelemVal;
            struct indelemlistValue *indelemlistVal;
        };
        struct indelemlistIndexedelemValue {
            struct indexedelemValue *indexedelemVal;
        };
    };

    indelemlistType valType;
};

enum indexedelemType {
    LcuExprRcu
};

struct indexedelemValue {
    union value {
        struct exprValue *exprVal;
    };

    indexedelemType valType;
};

enum blockType {
    LcuStmtListRcu
};

struct blockValue {
    union value {
        struct stmtListValue *stmtListVal;
    };

    blockType valType;
};

enum funcdefType {
    IdIdlistBlock,
    IdlistBlock
};

struct funcdefValue {
    union value {
        struct funcdefIdIdlistValue {
            std::string strVal;
            struct idlistValue *idlistVal;
            struct blockValue *blockVal;
        };
        struct funcdefIdlistValue {
            struct idlistValue *idlistVal;
            struct blockValue *blockVal;
        };
    };

    funcdefType valType;
};

enum constTypes {
    Int,
    Double,
    String,
    Empty,
    Bool
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
    Id,
    IdlistCommaId,
    Empty
};

struct idlistValue {
    union value {
        struct idlistIDValue {
            struct idValue *idVal;
        };
        struct idlistIdlistValue {
            struct idlistValue *idlistVal;
            struct idValue *idVal;
        };
    };

    idlistType valType;
};

enum ifstmtType {
    LparExprRparElse
};

struct ifstmtValue {
    union value {
        struct ifstmtBlockValue{
            struct exprValue *valType;
            struct stmtValue *stmtVal;
            struct elseValue *elseVal;
        };
    };

    ifstmtType valType;
};

enum elseType {
    ElseStmt,
    Empty
};

struct elseValue {
    union value {
        struct stmtValue *stmtVal;
    };

    elseType valType;
};

enum whilestmtType {
    LparExprRparStmt
};

struct whilestmtValue {
    union value {
        struct whilestmtStmtValue {
            struct exprValue *exprVal;
            struct stmtValue *stmtVal;
        };
    };

    whilestmtType valType;
};

enum forstmtType {
    LparElistRparStmt
};

struct forstmtValue {
    union Value {
        struct forstmtStmtValue {
            struct elistValue *elistVal;
            struct exprValue *exprVal;
            struct stmtValue *stmtVal;
        };
    };

    forstmtType valType;
};

enum returnstmtType {
    ReturnRet
};

struct returnstmtValue {
    union value {
        struct retValue *retVal;
    };

    returnstmtType valType;
};

enum retType {
    Expr,
    Empty
};

struct retValue {
    union value {
        struct exprValue *exprVal;
    };

    retType valType;
};

#endif /* __TYPES_H */