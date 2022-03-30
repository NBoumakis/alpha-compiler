#include <string>

enum ConstTypes {
    INT,
    DOUBLE,
    STRING,
    BOOL,
    NIL
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
    ID,
    MEMBER
};

struct lvalueValue {
    union value {
        std::string strVal;
        struct memberValue memberVal;
    };

    lvalueTypes valType;
};

struct memberValue {
    union value {
        struct {
            struct lvalueValue lvalueVal;
            std::string id;
        };
        struct
        {
            struct lvalueValue lvalueVal;
            struct exprValue exprVal;
        };
    };
};
