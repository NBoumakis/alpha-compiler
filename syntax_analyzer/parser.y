%{
    #include <iostream>
    #include <unordered_set>
    #include <stack>
    #include <string.h>
    #include "types.h"
    #include "scope.h"
    
    #include "rules.h"

    #include "colors.h"

    int yyerror(const char* yaccProvidedMessage){
        std::cerr << REDB "Grammar error: " << yaccProvidedMessage<< RST <<std::endl;
        return 0;
    }


    extern int yylineno;
    extern char* yytext;


    extern int yylex();
    extern int yyparse();
    extern FILE* yyin;

    extern Scope symbolTableObj;
    extern unsigned int scopeLevel;
    extern std::unordered_set<std::string> libFunctions;
    extern unsigned int funcDepth;
%}

%union{

#include "types.h"
    int intValue;
    double realValue;
    programValue *programVal;
    stmtListValue *stmtListVal;
    stmtValue *stmtVal;
    exprValue *exprVal;
    termValue *termVal;
    assignexprValue *assignexprVal;
    primaryValue *primaryVal;
    lvalueValue *lvalueVal;
    memberValue *memberVal;
    callValue *callVal;
    callsuffixValue *callsuffixVal;
    normcallValue *normcallVal;
    methodcallValue *methodcallVal;
    elistValue *elistVal;
    exprOptRptValue *exprOptRptVal;
    objectdefValue *objectdefVal;
    indexedValue *indexedVal;
    indelemlistValue *indelemlistVal;
    indexedelemValue *indexedelemVal;
    blockValue *blockVal;
    funcdefValue *funcdefVal;
    constValue *constVal;
    idlistValue *idlistVal;
    
    ifstmtValue *ifstmtVal;
    elseValue *elseVal;
    whilestmtValue *whilestmtVal;
    forstmtValue *forstmtVal;
    returnstmtValue *returnstmtVal;
    retValue *retVal;
    char* stringVal;
    Symbol* symPointer;
};



%token  <stringVal> ID
%token  IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE AND NOT OR LOCAL TRUE FALSE NIL
%token  ASSIGN PLUS MINUS MUL DIV MOD EQUAL NEQUAL PLUS_PLUS MINUS_MINUS GT GE LT LE
%token  <intValue> intNumber
%token  <realValue> realNumber
%token  L_CURLY_BRACKET R_CURLY_BRACKET L_SQUARE_BRACKET R_SQUARE_BRACKET L_PARENTHESIS R_PARENTHESIS SEMICOLON COMMA COLON NAMESPACE DOT DOUBLE_DOT
%token  <stringVal> STRING

/* Non-terminal types */
%type <programVal> program
%type <stmtListVal> stmtList
%type <stmtVal> stmt
%type <exprVal> expr
%type <termVal> term
%type <assignexprVal> assignexpr
%type <primaryVal> primary
%type <lvalueVal> lvalue
%type <memberVal> member
%type <callVal> call
%type <callsuffixVal> callsuffix
%type <normcallVal> normcall
%type <methodcallVal> methodcall
%type <elistVal> elist
%type <exprOptRptVal> exprOptRpt
%type <objectdefVal> objectdef
%type <indexedVal> indexed
%type <indelemlistVal> indelemlist
%type <indexedelemVal>  indexedelem
%type <blockVal> block

%type <stringVal> funcname
%type <symPointer> funcprefix
%type <funcdefVal> funcdef
%type <constVal> const
%type <idlistVal> idlist
%type <ifstmtVal> ifstmt
%type <elseVal> else
%type <whilestmtVal> whilestmt
%type <forstmtVal> forstmt
%type <returnstmtVal> returnstmt
%type <retVal> ret

/*Associativity and priority */
%right ASSIGN
%left OR
%left AND
%nonassoc EQUAL NEQUAL
%nonassoc GT GE LT LE
%left PLUS MINUS
%left MUL DIV MOD
%right NOT PLUS_PLUS MINUS_MINUS UMINUS
%left DOT DOUBLE_DOT
%left L_SQUARE_BRACKET R_SQUARE_BRACKET
%left L_PARENTHESIS R_PARENTHESIS

%start program

%%

program:     stmtList       {
                                std::cout << BGRN "Rule program -> stmtlist" RST << std::endl;
                                $$ = Manage_program($stmtList);
                            }
            ;

stmtList:    stmtList stmt  {
                                std::cout << BGRN "Rule stmtList -> stmtlist stmt" RST << std::endl;
                                $$ = Manage_stmtList_stmt($1, $stmt);
                            }
            |               {
                                std::cout << BGRN "Rule stmtList -> ε" RST << std::endl;
                                $$ = Manage_stmtList();
                            }
            ;

stmt:     expr SEMICOLON        {
                                    std::cout << BGRN "Rule stmt -> expr;" RST << std::endl;
                                    $$ = Manage_stmt_expr($1);
                                }
        | ifstmt                {
                                    std::cout << BGRN "Rule stmt -> ifstmt" RST << std::endl;
                                    $$ = Manage_stmt_ifstmt($1);
                                }
        | whilestmt             {
                                    std::cout << BGRN "Rule stmt -> whilestmt" RST << std::endl;
                                    $$ = Manage_stmt_whilestmt($1);
                                }
        | forstmt               {
                                    std::cout << BGRN "Rule stmt -> forstmt" RST << std::endl;
                                    $$ = Manage_stmt_forstmt($1);
                                }
        | returnstmt            {
                                    std::cout << BGRN "Rule stmt -> returnstmt" RST << std::endl;
                                    $$ = Manage_stmt_returnstmt($1);
                                }
        | BREAK SEMICOLON       {
                                    std::cout << BGRN "Rule stmt -> break;" RST << std::endl;
                                    $$ = Manage_stmt_break();
                                }
        | CONTINUE SEMICOLON    {
                                    std::cout << BGRN "Rule stmt -> continue;" RST << std::endl;
                                    $$ = Manage_stmt_continue();
                                }
        | block                 {
                                    std::cout << BGRN "Rule stmt -> block" RST << std::endl;
                                    $$ = Manage_stmt_block($1);
                                }
        | funcdef               {
                                    std::cout << BGRN "Rule stmt -> funcdef" RST << std::endl;
                                    $$ = Manage_stmt_funcdef($1);
                                }
        | SEMICOLON             {
                                    std::cout << BGRN "Rule stmt -> ;" RST << std::endl;
                                    $$ = Manage_stmt_semicolon();
                                }
        ;

expr:     assignexpr            {
                                    std::cout << BGRN "Rule expr -> assignexpr" RST << std::endl;
                                    $$ = Manage_expr_assignexpr($1);
                                }
        | expr PLUS expr        {
                                    std::cout << BGRN "Rule expr -> expr + expr" RST << std::endl;
                                    $$ = Manage_expr_expr_PLUS_expr($1, $3);}
        | expr MINUS expr       {
                                    std::cout << BGRN "Rule expr -> expr - expr" RST << std::endl;
                                    $$ = Manage_expr_expr_MINUS_expr($1, $3);
                                }
        | expr MUL expr         {
                                    std::cout << BGRN "Rule expr -> expr * expr" RST << std::endl;
                                    $$ = Manage_expr_expr_MUL_expr($1, $3);
                                }
        | expr DIV expr         {
                                    std::cout << BGRN "Rule expr -> expr / expr" RST << std::endl;
                                    $$ = Manage_expr_expr_DIV_expr($1, $3);
                                }
        | expr MOD expr         {
                                    std::cout << BGRN "Rule expr -> expr % expr" RST << std::endl;
                                    $$ = Manage_expr_expr_MOD_expr($1, $3);
                                }
        | expr GT expr          {
                                    std::cout << BGRN "Rule expr -> expr > expr" RST << std::endl;
                                    $$ = Manage_expr_expr_GT_expr($1, $3);
                                }
        | expr GE expr          {
                                    std::cout << BGRN "Rule expr -> expr >= expr" RST << std::endl;
                                    $$ = Manage_expr_expr_GE_expr($1, $3);
                                }
        | expr LT expr          {
                                    std::cout << BGRN "Rule expr -> expr < expr" RST << std::endl;
                                    $$ = Manage_expr_expr_LT_expr($1, $3);
                                }
        | expr LE expr          {
                                    std::cout << BGRN "Rule expr -> expr <= expr" RST << std::endl;
                                    $$ = Manage_expr_expr_LE_expr($1, $3);
                                }
        | expr EQUAL expr       {
                                    std::cout << BGRN "Rule expr -> expr == expr" RST << std::endl;
                                    $$ = Manage_expr_expr_EQUAL_expr($1, $3);
                                }
        | expr NEQUAL expr      {
                                    std::cout << BGRN "Rule expr -> expr != expr" RST << std::endl;
                                    $$ = Manage_expr_expr_NEQUAL_expr($1, $3);
                                }
        | expr AND expr         {
                                    std::cout << BGRN "Rule expr -> expr and expr" RST << std::endl;
                                    $$ = Manage_expr_expr_AND_expr($1, $3);
                                }
        | expr OR expr          {
                                    std::cout << BGRN "Rule expr -> expr or expr" RST << std::endl;
                                    $$ = Manage_expr_expr_OR_expr($1, $3);
                                }
        | term                  {
                                    std::cout << BGRN "Rule expr -> term" RST << std::endl;
                                    $$ = Manage_expr_term($1);
                                }
        ;

term:     L_PARENTHESIS expr R_PARENTHESIS  {
                                                std::cout << BGRN "Rule term -> (expr)" RST << std::endl;
                                                $$ = Manage_term_LPexprRP($2);
                                            }
        | NOT expr                          {
                                                std::cout << BGRN "Rule term -> not expr" RST << std::endl;
                                                $$ = Manage_term_notexpr($2);
                                            }
        | PLUS_PLUS lvalue                  {
                                                std::cout << BGRN "Rule term -> ++lvalue" RST << std::endl;
                                                $$ = Manage_term_PPlval($2);
                                            }
        | lvalue PLUS_PLUS                  {
                                                std::cout << BGRN "Rule term -> lvalue++" RST << std::endl;
                                                $$ = Manage_term_lvaluePP($1);
                                            }
        | MINUS_MINUS lvalue                {
                                                std::cout << BGRN "Rule term -> --lvalue" RST << std::endl;
                                                $$ = Manage_term_MMlval($2);
                                            }
        | lvalue MINUS_MINUS                {
                                                std::cout << BGRN "Rule term -> lvalue--" RST << std::endl;
                                                $$ = Manage_term_lvalueMM($1);
                                            }
        | primary                           {
                                                std::cout << BGRN "Rule term -> primary" RST << std::endl;
                                                $$ = Manage_term_primary($1);
                                            }
        | MINUS expr %prec UMINUS           {
                                                std::cout << BGRN "Rule term -> -expr Uminus" RST << std::endl;
                                                $$ = Manage_term_minusexpr($2);
                                            }
        ;

assignexpr:  lvalue ASSIGN expr {
                                    std::cout << BGRN "Rule assignexpr -> lvalue=expr" RST << std::endl;
                                    $$ = Manage_assignexpr_lvalueASSIGNexpr($1, $3);
                                }
            ;

primary:  lvalue                                {
                                                   std::cout << BGRN "Rule primary -> lvalue" RST << std::endl;
                                                   $$ = Manage_primary_lvalue($1);
                                                }
        | call                                  {
                                                   std::cout << BGRN "Rule primary -> call" RST << std::endl;
                                                   $$ = Manage_primary_call($1);
                                                }
        | objectdef                             {
                                                   std::cout << BGRN "Rule primary -> objectdef" RST << std::endl;
                                                   $$ = Manage_primary_objectdef($1);
                                                }
        | L_PARENTHESIS funcdef R_PARENTHESIS   {
                                                   std::cout << BGRN "Rule primary -> (funcdef)" RST << std::endl;
                                                   $$ = Manage_primary_LPfuncdefRP($2);
                                                }
        | const                                 {
                                                   std::cout << BGRN "Rule primary -> const" RST << std::endl;
                                                   $$ = Manage_primary_const($1);
                                                }
        ;

lvalue:   ID            {
                            std::cout << BGRN "Rule lvalue -> id" RST << std::endl;
                            $$ = Manage_lvalue_id($1);
                        }
        | LOCAL ID      {
                            std::cout << BGRN "Rule lvalue -> local id" RST << std::endl;
                            $$ = Manage_lvalue_localid($2);
                        }
        | NAMESPACE ID  {
                            std::cout << BGRN "Rule lvalue -> namespace id" RST << std::endl;
                            $$ = Manage_lvalue_globalid($2);
                        }
        | member        {
                            std::cout << BGRN "Rule lvalue -> member" RST << std::endl;
                            $$ = Manage_lvalue_member($1);
                        }
        ;

member:   lvalue DOT ID                                     {
                                                                std::cout << BGRN "Rule member -> lvalue.id" RST << std::endl;
                                                                $$ = Manage_member_lvalueDOTid($1, $3);
                                                            }
        | lvalue L_SQUARE_BRACKET expr R_SQUARE_BRACKET     {
                                                                std::cout << BGRN "Rule member -> lvalue[expr]" RST << std::endl;
                                                                $$ = Manage_member_lvalueLSBexprRSB($1, $3);
                                                            }
        | call DOT ID                                       {
                                                                std::cout << BGRN "Rule member -> call.id" RST << std::endl;
                                                                $$ = Manage_member_callDOTid($1, $3);
                                                            }
        | call L_SQUARE_BRACKET expr R_SQUARE_BRACKET       {
                                                                std::cout << BGRN "Rule member -> call[expr]" RST << std::endl;
                                                                $$ = Manage_member_callLSBexprRSB($1, $3);
                                                            }
        ;

call:     call L_PARENTHESIS elist R_PARENTHESIS                                        {
                                                                                            std::cout << BGRN "Rule call -> call(elist)" RST << std::endl;
                                                                                            $$ = Manage_call_callLPelistRP($1, $3);
                                                                                        }
        | lvalue callsuffix                                                             {
                                                                                            std::cout << BGRN "Rule call -> lvalue callsuffix" RST << std::endl;
                                                                                            $$ = Manage_call_lvaluecallsuffix($1, $2);
                                                                                        }
        | L_PARENTHESIS funcdef R_PARENTHESIS L_PARENTHESIS elist R_PARENTHESIS         {
                                                                                            std::cout << BGRN "Rule call -> (funcdef)(elist)" RST << std::endl;
                                                                                            $$ = Manage_call_LPfuncdefRPLPelistRP($2, $5);
                                                                                        }
        ;

callsuffix:   normcall      {
                                std::cout << BGRN "Rule callsuffix -> normcall" RST << std::endl;
                                $$ = Manage_callsuffix_normcall($1);}
            | methodcall    {
                                std::cout << BGRN "Rule callsuffix -> methodcall" RST << std::endl;
                                $$ = Manage_callsuffix_methodcall($1);
                            }
            ;

normcall:     L_PARENTHESIS elist R_PARENTHESIS                 {
                                                                    std::cout << BGRN "Rule normcall -> (elist)" RST << std::endl;
                                                                    $$ = Manage_normcall_LPelistRP($2);
                                                                }
            ;

methodcall:   DOUBLE_DOT ID L_PARENTHESIS elist R_PARENTHESIS   {
                                                                    std::cout << BGRN "Rule methodcall -> ..id(elist)" RST << std::endl;
                                                                    $$ = Manage_methodcall_DDOTidLPelistRP($2, $4);
                                                                }
            ;

elist:   exprOptRpt         {
                                std::cout << BGRN "Rule elist -> exprOptRpt" RST << std::endl;
                                $$ = Manage_elist_exprOptRpt($1);
                            }
        |                   {
                                std::cout << BGRN "Rule elist -> ε" RST << std::endl;
                                $$ = Manage_elist();
                            }
       ;

exprOptRpt:   expr COMMA exprOptRpt     {
                                            std::cout << BGRN "Rule exprOptRpt -> expr, exprOptRpt" RST << std::endl;
                                            $$ = Manage_exprOR_exprOR($1, $3);
                                        }
            | expr                      {
                                            std::cout << BGRN "Rule exprOptRpt -> expr" RST << std::endl;
                                            $$ = Manage_exprOR_expr($1);
                                        }
            ;

objectdef:    L_SQUARE_BRACKET elist R_SQUARE_BRACKET       {
                                                                std::cout << BGRN "Rule objectdef -> [elist]" RST << std::endl;
                                                                $$ = Manage_objectdef_LSBelistRSB($2);
                                                            }
            | L_SQUARE_BRACKET indexed R_SQUARE_BRACKET     {
                                                                std::cout << BGRN "Rule objectdef -> [indexed]" RST << std::endl;
                                                                $$ = Manage_objectdef_LSBindexedRSB($2);
                                                            }
            ;


indexed:  indelemlist   {
                            std::cout << BGRN "Rule indexed -> indelemlist" RST << std::endl;
                            $$ = Manage_indexed($1);
                        }
        ;

indelemlist:  indexedelem COMMA indelemlist     {
                                                    std::cout << BGRN "Rule indelemlist -> indexedelem, indelemlist" RST << std::endl;
                                                    $$ = Manage_indelemlist($1, $3);
                                                }
            | indexedelem                       {
                                                    std::cout << BGRN "Rule indelemlist -> indexedelem" RST << std::endl;
                                                    $$ = Manage_indelemlist_indexedelem($1);
                                                }
            ;


indexedelem:  L_CURLY_BRACKET expr COLON expr R_CURLY_BRACKET   {
                                                                    std::cout << BGRN "Rule indexedelem -> {expr:expr}" RST << std::endl;
                                                                    $$ = Manage_indexedelem_LCB_expr_COLON_expr_RCB($2, $4);
                                                                }
            ;

block:    L_CURLY_BRACKET {++scopeLevel;} stmtList R_CURLY_BRACKET {symbolTableObj.hide(scopeLevel--);}
            {
                std::cout << BGRN "Rule block -> { stmtList }" RST << std::endl;
                $$ = Manage_block_LCBstmtRCB($3);
            }
        ;

funcname:     ID    {
                        size_t id_len = strlen($ID);
                        $funcname = new char[strlen($ID)];
                        strncpy($funcname, $ID, id_len);
                        $funcname[id_len] = '\0';
                    }
            |       {
                        std::string id = newTmpFuncname();
                        $funcname = new char[id.length()];
                        std::size_t length = id.copy($funcname, id.length());
                        $funcname[length] = '\0';
                    }
            ;

funcprefix:   FUNCTION funcname {
                                    std::cout << BGRN
                                        "Rule funcprefix -> function funcname, line " << yylineno << RST
                                        << std::endl;

                                    $funcprefix = Manage_funcprefix($funcname);
                                }
            ;

funcargs:     L_PARENTHESIS {++funcDepth;} idlist R_PARENTHESIS
                                {
                                    std::cout << BGRN
                                        "Rule funcargs -> ( idlist ), line " << yylineno << RST
                                        << std::endl;

                                    Manage_funcargs($idlist);
                                }
            ;

funcbody:     block     {
                            std::cout << BGRN
                                "Rule funcbody -> block, line " << yylineno << RST
                                << std::endl;

                            --funcDepth;
                        }
            ;

funcdef:  funcprefix funcargs funcbody
            {
                std::cout << BGRN "Rule funcdef -> funcprefix funcargs funcbody, line " << yylineno << RST << std::endl;
            }
        ;

const:    intNumber     {
                            std::cout << BGRN "Rule const -> intNumber" RST << std::endl;
                            $$ = Manage_const_int($1);
                        }
        | realNumber    {
                            std::cout << BGRN "Rule const -> realNumber" RST << std::endl;
                            $$ = Manage_const_real($1);
                        }
        | STRING        {
                            std::cout << BGRN "Rule const -> string" RST << std::endl;
                            $$ = Manage_const_string($1);
                        }
        | NIL           {   
                            std::cout << BGRN "Rule const -> nil" RST << std::endl;
                            $$ = Manage_const_nil();
                        }
        | TRUE          {
                            std::cout << BGRN "Rule const -> true" RST << std::endl;
                            $$ = Manage_const_true();
                        }
        | FALSE         {
                            std::cout << BGRN "Rule const -> false" RST << std::endl;
                            $$ = Manage_const_false();
                        }
        ;

idlist:   ID    {
                    std::cout << BGRN "Rule idlist -> id" RST << std::endl;
                    $$ = Manage_idlist_ID($1);
                }
        | ID COMMA idlist   {
                                std::cout << BGRN "Rule idlist -> idlist, id" RST << std::endl;
                                $$ = Manage_idlist_idlist_comma_id($3, $1);
                            }
        |                   {
                                std::cout << BGRN "Rule idlist -> ε" RST << std::endl;
                                $$ = Manage_idlist();
                            }
        ;

ifstmt:   IF L_PARENTHESIS expr R_PARENTHESIS stmt else     {   
                                                                std::cout << BGRN "Rule ifstmt -> if (expr) stmt else" RST << std::endl;
                                                                $$ = Manage_ifstmt($3, $5, $6);
                                                            }
        ;

else:     ELSE stmt     {   
                            std::cout << BGRN "Rule else -> else stmt" RST << std::endl;
                            $$ = Manage_else_stmt($2);
                        }
        |               {   
                            std::cout << BGRN "Rule else -> ε" RST << std::endl;
                            $$ = Manage_else();
                        }
        ;

whilestmt:    WHILE L_PARENTHESIS expr R_PARENTHESIS stmt   {   
                                                                std::cout << BGRN "Rule whilestmt -> (expr) stmt" RST << std::endl;
                                                                $$ = Manage_whilestmt($3, $5);
                                                            }
            ;

forstmt:      FOR L_PARENTHESIS elist SEMICOLON expr SEMICOLON elist R_PARENTHESIS stmt     {
                                                                                                std::cout << BGRN "Rule forstmt -> for (elist ; expr ; elist) stmt " RST << std::endl;
                                                                                                $$ = Manage_for($3, $5, $7, $9);
                                                                                            }
            ;

returnstmt:   RETURN ret SEMICOLON      {       
                                            std::cout << BGRN "Rule returnstmt -> ret;" RST << std::endl;
                                            $$ = Manage_returnstmt($2);
                                        }
            ;

ret:      expr      {
                        std::cout << BGRN "Rule ret -> expr" RST << std::endl;
                        $$ = Manage_ret_expr($1);
                    }
        |           {   
                        std::cout << BGRN "Rule ret -> ε" RST << std::endl;
                        $$ = Manage_ret();
                    }
        ;
