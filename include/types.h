#include <string>

struct memberValue;

enum ConstTypes {
    INT,
    DOUBLE,
    STRING1,
    BOOL,
    NIL1
};

struct constValue {
    union value {
        int intVal;
        double doubleVal;
        std::string stringVal;
        bool boolVal;
    };

    ConstTypes valType;
};

enum lvalueTypes {
    ID1,
    MEMBER
};

struct lvalueValue {
    union value {
        std::string strVal;
        struct memberValue *memberVal;
    };

    lvalueTypes valType;
};

struct memberValue {
    union value {
        struct {
            struct lvalueValue lvalueVal;
            std::string id;
        } lvalid;
        struct
        {
            struct lvalueValue lvalueVal;
            struct exprValue *exprVal;
        } lvalexpr;
    };
};
