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

struct opValue {
    union value {
        std::string PLUS;
        std::string MINUS;
        std::string MUL;
        std::string DIV;
        std::string MOD;
        std::string GT;
        std::string GE;
        std::string LT;
        std::string LE;
        std::string EQUAL;
        std::string NEQUAL;
        std::string AND;
        std::string OR;
    };
};

enum termType {
    EXPR,
    LVALUE,
    PRIMARY
};

struct termValue {
    union value {
        struct termEXPRBRACKETSValue {
            std::string L_PARENTHSESIS;
            struct exprValue *exprVal;
            std::string R_PARENTHSESIS;
        };
        struct termNOTEXPRValue {
            std::string NOT;
            struct exprValue *exprVal;
        };
        struct termPLUS_PLUSLVALUEValue {
            std::string PLUS_PLUS;
            struct lvalueValue *lvalueVal;
        };
        struct termLVALUEPLUS_PLUSValue {
            struct lvalueValue lvalueVal;
            std::string PLUS_PLUS;
        };
        struct termMINUS_MINUSLVALUEValue {
            std::string MINUS_MINUS;
            struct lvalueValue *lvalueVal;
        };
        struct termLVALUEMINUS_MINUSValue {
            struct lvalueValue lvalueVal;
            std::string MINUS_MINUS;
        };
        struct termPRIMARYValue {
            struct primaryValue *primaryVal;
        };
        struct termMINUSValue {
            std::string MINUS;
            struct exprValue *exprVal;
        };
    };

    termType valType;
};

enum assignexprType {
    LVALUE,
    EXPR
};

struct assignexprValue {
    union value {
        struct lvalueValue *lvalueVal;
        struct exprValue *exprVal;
    };

    assignexprType valType;
};

enum primaryType {
    LVALUE,
    CALL,
    OBJECTDEF,
    FUNCDEF,
    CONST
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
    ID,
    MEMBER
};

struct lvalueValue {
    union value {
        std::string strVal;
        struct lvalueLOCALIDValue {
            std::string LOCAL;
            std::string id;
        };
        struct lvalueNAMESPACEIDValue {
            std::string NAMESPACE;
            std::string id;
        };
        struct memberValue *memberVal;
    };

    lvalueType valType;
};

enum memberType {
    LVALUE,
    CALL,
    ID,
    EXPR
};

struct memberValue {
    union value {
        struct memberLVALUEDOTValue {
            struct lvalueValue *lvalueVal;
            std::string id;
        };
        struct memberLVALUEEXPRValue {
            struct lvalueValue *lvalueVal;
            struct exprValue *exprVal;
        };
        struct memberCALLDOTValue {
            struct callValue *callVal;
            std::string id;
        };
        struct memberCALLEXPRValue {
            struct callValue *callVal;
            struct exprValue *exprVal; 
        };
    };

    memberType valTypes;
};

enum callType{
    CALL,
    ELIST,
    LVALUE,
    CALLSUFFIX,
    FUNCDEF
};


struct callValue {
    union value {
        struct callELISTValue {
            struct callValue *callVal;
            struct elistValue *elistVal;
        };
        struct callLVALUEValue{
            struct lvalueValue *lvalueVal;
            struct callsuffixValue *callsuffixVAl;
        };
        struct callFUNCDEFValue{
            struct funcdefValue *funcdefVa;
            struct elistValue *elistVAl;
        };
    };

    callType valType;

};

enum callsuffixType {
    NORMCALL,
    METHODCALL
};

struct callsuffixValue{
    union value {
        struct normcallValue *normcallVal;
        struct methodcallValue *methodcallVal;
    };
};

enum normcallType {
    ELIST
};

struct normcallValue {
    union value {
        struct elistValue *elistVal;
    };

    normcallType valType;
};

enum methodcallType{
    ID,
    ELIST
};

struct methodcallValue {
    union value {
        std::string strVal;
        struct elistValue *elistVal;
    };

    methodcallType valType;
};

enum elistType {
    EXPROPTRPT
};

struct elistValue {
    union value {
        struct exprOptRptValue *exprOptRptVal;
    };

    elistType valType;
};

enum exprOptRptType {
    EXPR,
    EXPROPTRPT
};

struct exprOptRptValue {
    union value {
        struct exprOptRptCOMMAValue {
            struct exprOptRpt *exprOptRptVal;
        };
        struct exprOptRptEXPRValue {
            struct exprValue *exprVal;
        };
    };

    exprOptRptType valType;
};

enum objectdefType {
    ELIST,
    INDEXED,
    VOID
};

struct objectdefValue {
    union value {
        struct objectdefELISTValue {
            struct elistValue *elistVal;
        };
        struct objectdefINDEXEDValue {
            struct indexedValue *indexedVal;
        };
    };

    objectdefType valType;
};

enum indexedType {
    INDELEMLIST,
    VOID
};

struct indexedValue {
    union value {
        struct indelemlistValue *indelemlistVal;
    };

    indexedType valType;
};

enum indelemlistType {
    INDEXEDELEM,
    INDELEMLIST
};

struct indelemlistValue {
    union value {
        struct indelemlistCOMMAValue {
            struct indexedelemValue *indexedelemVal;
            struct indelemlistValue *indelemlistVal;
        };
        struct indelemlistINDEXEDELEMValue {
            struct indexedelemValue *indexedelemVal;
        };
    };

    indelemlistType valType;
};

enum indexedelemType {
    EXPR
};

struct indexedelemValue {
    union value {
        struct exprValue *exprVal;
    };

    indexedelemType valType;
};

enum blockType{
    BLOCKSTMT
};

struct blockValue {
    union value {
        struct blockstmtValue *blockstmtVal;
    };

    blockType valType;
};

enum blockstmtType {
    STMT,
    BLOCKSTMT
};

struct blockstmtValue {
    union value {
        struct stmtValue *stmtVal;
        struct blockstmtValue *blockstmtVal;
    };

    blockstmtType valType;
};

enum funcdefType {
    ID,
    IDLIST,
    BLOCK
};

struct funcdefValue {
    union value{
        struct funcdefIDValue{
            std::string strVal;
            struct idlistValue *idlistVal;
            struct blockValue *blockVal;
        };
        struct funcdefNOIDValue{
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