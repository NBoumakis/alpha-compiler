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
                                std::cout << BGRN "Rule program -> stmtlist, line " << yylineno << RST << std::endl;
                                $$ = Manage_program($stmtList);
                            }
            ;

stmtList:    stmtList[derivated] stmt   {
                                            std::cout << BGRN "Rule stmtList -> stmtlist stmt, line " << yylineno << RST << std::endl;
                                            $$ = Manage_stmtList_stmt($derivated, $stmt);
                                        }
            |                           {
                                            std::cout << BGRN "Rule stmtList -> ε, line " << yylineno << RST << std::endl;
                                            $$ = Manage_stmtList();
                                        }
            ;

stmt:     expr SEMICOLON        {
                                    std::cout << BGRN "Rule stmt -> expr;, line " << yylineno << RST << std::endl;
                                    $$ = Manage_stmt_expr($expr);
                                }
        | ifstmt                {
                                    std::cout << BGRN "Rule stmt -> ifstmt, line " << yylineno << RST << std::endl;
                                    $$ = Manage_stmt_ifstmt($ifstmt);
                                }
        | whilestmt             {
                                    std::cout << BGRN "Rule stmt -> whilestmt, line " << yylineno << RST << std::endl;
                                    $$ = Manage_stmt_whilestmt($whilestmt);
                                }
        | forstmt               {
                                    std::cout << BGRN "Rule stmt -> forstmt, line " << yylineno << RST << std::endl;
                                    $$ = Manage_stmt_forstmt($forstmt);
                                }
        | returnstmt            {
                                    std::cout << BGRN "Rule stmt -> returnstmt, line " << yylineno << RST << std::endl;
                                    $$ = Manage_stmt_returnstmt($returnstmt);
                                }
        | BREAK SEMICOLON       {
                                    std::cout << BGRN "Rule stmt -> break;, line " << yylineno << RST << std::endl;
                                    $$ = Manage_stmt_break();
                                }
        | CONTINUE SEMICOLON    {
                                    std::cout << BGRN "Rule stmt -> continue;, line " << yylineno << RST << std::endl;
                                    $$ = Manage_stmt_continue();
                                }
        | block                 {
                                    std::cout << BGRN "Rule stmt -> block, line " << yylineno << RST << std::endl;
                                    $$ = Manage_stmt_block($block);
                                }
        | funcdef               {
                                    std::cout << BGRN "Rule stmt -> funcdef, line " << yylineno << RST << std::endl;
                                    $$ = Manage_stmt_funcdef($funcdef);
                                }
        | SEMICOLON             {
                                    std::cout << BGRN "Rule stmt -> ;, line " << yylineno << RST << std::endl;
                                    $$ = Manage_stmt_semicolon();
                                }
        ;

expr:     assignexpr            {
                                    std::cout << BGRN "Rule expr -> assignexpr, line " << yylineno << RST << std::endl;
                                    $$ = Manage_expr_assignexpr($assignexpr);
                                }
        | expr[left] PLUS expr[right]   {
                                            std::cout << BGRN "Rule expr -> expr + expr, line " << yylineno << RST << std::endl;
                                            $$ = Manage_expr_expr_PLUS_expr($left, $right);
                                        }
        | expr[left] MINUS expr[right]  {
                                            std::cout << BGRN "Rule expr -> expr - expr, line " << yylineno << RST << std::endl;
                                            $$ = Manage_expr_expr_MINUS_expr($left, $right);
                                        }
        | expr[left] MUL expr[right]    {
                                            std::cout << BGRN "Rule expr -> expr * expr, line " << yylineno << RST << std::endl;
                                            $$ = Manage_expr_expr_MUL_expr($left, $right);
                                        }
        | expr[left] DIV expr[right]    {
                                            std::cout << BGRN "Rule expr -> expr / expr, line " << yylineno << RST << std::endl;
                                            $$ = Manage_expr_expr_DIV_expr($left, $right);
                                        }
        | expr[left] MOD expr[right]    {
                                            std::cout << BGRN "Rule expr -> expr % expr, line " << yylineno << RST << std::endl;
                                            $$ = Manage_expr_expr_MOD_expr($left, $right);
                                        }
        | expr[left] GT expr[right]     {
                                            std::cout << BGRN "Rule expr -> expr > expr, line " << yylineno << RST << std::endl;
                                            $$ = Manage_expr_expr_GT_expr($left, $right);
                                        }
        | expr[left] GE expr[right]     {
                                            std::cout << BGRN "Rule expr -> expr >= expr, line " << yylineno << RST << std::endl;
                                            $$ = Manage_expr_expr_GE_expr($1, $right);
                                        }
        | expr[left] LT expr[right]     {
                                            std::cout << BGRN "Rule expr -> expr < expr, line " << yylineno << RST << std::endl;
                                            $$ = Manage_expr_expr_LT_expr($left, $right);
                                        }
        | expr[left] LE expr[right]     {
                                            std::cout << BGRN "Rule expr -> expr <= expr, line " << yylineno << RST << std::endl;
                                            $$ = Manage_expr_expr_LE_expr($left, $right);
                                        }
        | expr[left] EQUAL expr[right]  {
                                            std::cout << BGRN "Rule expr -> expr == expr, line " << yylineno << RST << std::endl;
                                            $$ = Manage_expr_expr_EQUAL_expr($left, $right);
                                        }
        | expr[left] NEQUAL expr[right] {
                                            std::cout << BGRN "Rule expr -> expr != expr, line " << yylineno << RST << std::endl;
                                            $$ = Manage_expr_expr_NEQUAL_expr($left, $right);
                                        }
        | expr[left] AND expr[right]    {
                                            std::cout << BGRN "Rule expr -> expr and expr, line " << yylineno << RST << std::endl;
                                            $$ = Manage_expr_expr_AND_expr($left, $right);
                                        }
        | expr[left] OR expr[right]     {
                                            std::cout << BGRN "Rule expr -> expr or expr, line " << yylineno << RST << std::endl;
                                            $$ = Manage_expr_expr_OR_expr($left, $right);
                                        }
        | term                          {
                                            std::cout << BGRN "Rule expr -> term, line " << yylineno << RST << std::endl;
                                            $$ = Manage_expr_term($1);
                                        }
        ;

term:     L_PARENTHESIS expr R_PARENTHESIS  {
                                                std::cout << BGRN "Rule term -> (expr), line " << yylineno << RST << std::endl;
                                                $$ = Manage_term_LPexprRP($expr);
                                            }
        | NOT expr                          {
                                                std::cout << BGRN "Rule term -> not expr, line " << yylineno << RST << std::endl;
                                                $$ = Manage_term_notexpr($expr);
                                            }
        | PLUS_PLUS lvalue                  {
                                                std::cout << BGRN "Rule term -> ++lvalue, line " << yylineno << RST << std::endl;
                                                $$ = Manage_term_PPlval($lvalue);
                                            }
        | lvalue PLUS_PLUS                  {
                                                std::cout << BGRN "Rule term -> lvalue++, line " << yylineno << RST << std::endl;
                                                $$ = Manage_term_lvaluePP($lvalue);
                                            }
        | MINUS_MINUS lvalue                {
                                                std::cout << BGRN "Rule term -> --lvalue, line " << yylineno << RST << std::endl;
                                                $$ = Manage_term_MMlval($lvalue);
                                            }
        | lvalue MINUS_MINUS                {
                                                std::cout << BGRN "Rule term -> lvalue--, line " << yylineno << RST << std::endl;
                                                $$ = Manage_term_lvalueMM($lvalue);
                                            }
        | primary                           {
                                                std::cout << BGRN "Rule term -> primary, line " << yylineno << RST << std::endl;
                                                $$ = Manage_term_primary($primary);
                                            }
        | MINUS expr %prec UMINUS           {
                                                std::cout << BGRN "Rule term -> -expr Uminus, line " << yylineno << RST << std::endl;
                                                $$ = Manage_term_minusexpr($expr);
                                            }
        ;

assignexpr:  lvalue ASSIGN expr {
                                    std::cout << BGRN "Rule assignexpr -> lvalue=expr, line " << yylineno << RST << std::endl;
                                    $$ = Manage_assignexpr_lvalueASSIGNexpr($lvalue, $expr);
                                }
            ;

primary:  lvalue                                {
                                                   std::cout << BGRN "Rule primary -> lvalue, line " << yylineno << RST << std::endl;
                                                   $$ = Manage_primary_lvalue($lvalue);
                                                }
        | call                                  {
                                                   std::cout << BGRN "Rule primary -> call, line " << yylineno << RST << std::endl;
                                                   $$ = Manage_primary_call($call);
                                                }
        | objectdef                             {
                                                   std::cout << BGRN "Rule primary -> objectdef, line " << yylineno << RST << std::endl;
                                                   $$ = Manage_primary_objectdef($objectdef);
                                                }
        | L_PARENTHESIS funcdef R_PARENTHESIS   {
                                                   std::cout << BGRN "Rule primary -> (funcdef), line " << yylineno << RST << std::endl;
                                                   $$ = Manage_primary_LPfuncdefRP($funcdef);
                                                }
        | const                                 {
                                                   std::cout << BGRN "Rule primary -> const, line " << yylineno << RST << std::endl;
                                                   $$ = Manage_primary_const($const);
                                                }
        ;

lvalue:   ID            {
                            std::cout << BGRN "Rule lvalue -> id, line " << yylineno << RST << std::endl;
                            $$ = Manage_lvalue_id($ID);
                        }
        | LOCAL ID      {
                            std::cout << BGRN "Rule lvalue -> local id, line " << yylineno << RST << std::endl;
                            $$ = Manage_lvalue_localid($ID);
                        }
        | NAMESPACE ID  {
                            std::cout << BGRN "Rule lvalue -> namespace id, line " << yylineno << RST << std::endl;
                            $$ = Manage_lvalue_globalid($ID);
                        }
        | member        {
                            std::cout << BGRN "Rule lvalue -> member, line " << yylineno << RST << std::endl;
                            $$ = Manage_lvalue_member($member);
                        }
        ;

member:   lvalue DOT ID                                     {
                                                                std::cout << BGRN "Rule member -> lvalue.id, line " << yylineno << RST << std::endl;
                                                                $$ = Manage_member_lvalueDOTid($lvalue, $ID);
                                                            }
        | lvalue L_SQUARE_BRACKET expr R_SQUARE_BRACKET     {
                                                                std::cout << BGRN "Rule member -> lvalue[expr], line " << yylineno << RST << std::endl;
                                                                $$ = Manage_member_lvalueLSBexprRSB($lvalue, $expr);
                                                            }
        | call DOT ID                                       {
                                                                std::cout << BGRN "Rule member -> call.id, line " << yylineno << RST << std::endl;
                                                                $$ = Manage_member_callDOTid($call, $ID);
                                                            }
        | call L_SQUARE_BRACKET expr R_SQUARE_BRACKET       {
                                                                std::cout << BGRN "Rule member -> call[expr], line " << yylineno << RST << std::endl;
                                                                $$ = Manage_member_callLSBexprRSB($call, $expr);
                                                            }
        ;

call:     call[derivated] L_PARENTHESIS elist R_PARENTHESIS                         {
                                                                                        std::cout << BGRN "Rule call -> call(elist), line " << yylineno << RST << std::endl;
                                                                                        $$ = Manage_call_callLPelistRP($derivated, $elist);
                                                                                    }
        | lvalue callsuffix                                                         {
                                                                                        std::cout << BGRN "Rule call -> lvalue callsuffix, line " << yylineno << RST << std::endl;
                                                                                        $$ = Manage_call_lvaluecallsuffix($lvalue, $callsuffix);
                                                                                    }
        | L_PARENTHESIS funcdef R_PARENTHESIS L_PARENTHESIS elist R_PARENTHESIS     {
                                                                                        std::cout << BGRN "Rule call -> (funcdef)(elist), line " << yylineno << RST << std::endl;
                                                                                        $$ = Manage_call_LPfuncdefRPLPelistRP($funcdef, $elist);
                                                                                    }
        ;

callsuffix:   normcall      {
                                std::cout << BGRN "Rule callsuffix -> normcall, line " << yylineno << RST << std::endl;
                                $$ = Manage_callsuffix_normcall($normcall);
                            }
            | methodcall    {
                                std::cout << BGRN "Rule callsuffix -> methodcall, line " << yylineno << RST << std::endl;
                                $$ = Manage_callsuffix_methodcall($methodcall);
                            }
            ;

normcall:     L_PARENTHESIS elist R_PARENTHESIS                 {
                                                                    std::cout << BGRN "Rule normcall -> (elist), line " << yylineno << RST << std::endl;
                                                                    $$ = Manage_normcall_LPelistRP($elist);
                                                                }
            ;

methodcall:   DOUBLE_DOT ID L_PARENTHESIS elist R_PARENTHESIS   {
                                                                    std::cout << BGRN "Rule methodcall -> ..id(elist), line " << yylineno << RST << std::endl;
                                                                    $$ = Manage_methodcall_DDOTidLPelistRP($ID, $elist);
                                                                }
            ;

elist:   exprOptRpt         {
                                std::cout << BGRN "Rule elist -> exprOptRpt, line " << yylineno << RST << std::endl;
                                $$ = Manage_elist_exprOptRpt($exprOptRpt);
                            }
        |                   {
                                std::cout << BGRN "Rule elist -> ε, line " << yylineno << RST << std::endl;
                                $$ = Manage_elist();
                            }
       ;

exprOptRpt:   expr COMMA exprOptRpt[derivated]  {
                                                    std::cout << BGRN "Rule exprOptRpt -> expr, exprOptRpt, line " << yylineno << RST << std::endl;
                                                    $$ = Manage_exprOR_exprOR($expr, $derivated);
                                                }
            | expr                              {
                                                    std::cout << BGRN "Rule exprOptRpt -> expr, line " << yylineno << RST << std::endl;
                                                    $$ = Manage_exprOR_expr($expr);
                                                }
            ;

objectdef:    L_SQUARE_BRACKET elist R_SQUARE_BRACKET       {
                                                                std::cout << BGRN "Rule objectdef -> [elist], line " << yylineno << RST << std::endl;
                                                                $$ = Manage_objectdef_LSBelistRSB($elist);
                                                            }
            | L_SQUARE_BRACKET indexed R_SQUARE_BRACKET     {
                                                                std::cout << BGRN "Rule objectdef -> [indexed], line " << yylineno << RST << std::endl;
                                                                $$ = Manage_objectdef_LSBindexedRSB($indexed);
                                                            }
            ;


indexed:  indelemlist   {
                            std::cout << BGRN "Rule indexed -> indelemlist, line " << yylineno << RST << std::endl;
                            $$ = Manage_indexed($indelemlist);
                        }
        ;

indelemlist:  indexedelem COMMA indelemlist[derivated]  {
                                                            std::cout << BGRN "Rule indelemlist -> indexedelem, indelemlist, line " << yylineno << RST << std::endl;
                                                            $$ = Manage_indelemlist($indexedelem, $derivated);
                                                        }
            | indexedelem                               {
                                                            std::cout << BGRN "Rule indelemlist -> indexedelem, line " << yylineno << RST << std::endl;
                                                            $$ = Manage_indelemlist_indexedelem($indexedelem);
                                                        }
            ;


indexedelem:  L_CURLY_BRACKET expr[key] COLON expr[value] R_CURLY_BRACKET   {
                                                                                std::cout << BGRN "Rule indexedelem -> {expr:expr}, line " << yylineno << RST << std::endl;
                                                                                $$ = Manage_indexedelem_LCB_expr_COLON_expr_RCB($key, $value);
                                                                            }
            ;

block:    L_CURLY_BRACKET {++scopeLevel;} stmtList R_CURLY_BRACKET {symbolTableObj.hide(scopeLevel--);}
            {
                std::cout << BGRN "Rule block -> { stmtList }, line " << yylineno << RST << std::endl;
                $$ = Manage_block_LCBstmtRCB($stmtList);
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
                            std::cout << BGRN "Rule const -> intNumber, line " << yylineno << RST << std::endl;
                            $$ = Manage_const_int($intNumber);
                        }
        | realNumber    {
                            std::cout << BGRN "Rule const -> realNumber, line " << yylineno << RST << std::endl;
                            $$ = Manage_const_real($realNumber);
                        }
        | STRING        {
                            std::cout << BGRN "Rule const -> string, line " << yylineno << RST << std::endl;
                            $$ = Manage_const_string($STRING);
                        }
        | NIL           {
                            std::cout << BGRN "Rule const -> nil, line " << yylineno << RST << std::endl;
                            $$ = Manage_const_nil();
                        }
        | TRUE          {
                            std::cout << BGRN "Rule const -> true, line " << yylineno << RST << std::endl;
                            $$ = Manage_const_true();
                        }
        | FALSE         {
                            std::cout << BGRN "Rule const -> false, line " << yylineno << RST << std::endl;
                            $$ = Manage_const_false();
                        }
        ;

idlist:   ID    {
                    std::cout << BGRN "Rule idlist -> id, line " << yylineno << RST << std::endl;
                    $$ = Manage_idlist_ID($ID);
                }
        | ID COMMA idlist[derivated]    {
                                            std::cout << BGRN "Rule idlist -> idlist, id, line " << yylineno << RST << std::endl;
                                            $$ = Manage_idlist_idlist_comma_id($derivated, $ID);
                                        }
        |                               {
                                            std::cout << BGRN "Rule idlist -> ε, line " << yylineno << RST << std::endl;
                                            $$ = Manage_idlist();
                                        }
        ;

ifstmt:   IF L_PARENTHESIS expr R_PARENTHESIS stmt else     {
                                                                std::cout << BGRN "Rule ifstmt -> if (expr) stmt else, line " << yylineno << RST << std::endl;
                                                                $$ = Manage_ifstmt($expr, $stmt, $else);
                                                            }
        ;

else:     ELSE stmt     {
                            std::cout << BGRN "Rule else -> else stmt, line " << yylineno << RST << std::endl;
                            $$ = Manage_else_stmt($stmt);
                        }
        |               {
                            std::cout << BGRN "Rule else -> ε, line " << yylineno << RST << std::endl;
                            $$ = Manage_else();
                        }
        ;

whilestmt:    WHILE L_PARENTHESIS expr R_PARENTHESIS stmt   {
                                                                std::cout << BGRN "Rule whilestmt -> (expr) stmt, line " << yylineno << RST << std::endl;
                                                                $$ = Manage_whilestmt($expr, $stmt);
                                                            }
            ;

forstmt:      FOR L_PARENTHESIS elist[init] SEMICOLON expr SEMICOLON elist[postloop] R_PARENTHESIS stmt {
                                                                                                            std::cout << BGRN "Rule forstmt -> for (elist ; expr ; elist) stmt, line " << yylineno << RST << std::endl;
                                                                                                            $$ = Manage_for($init, $expr, $postloop, $stmt);
                                                                                                        }
            ;

returnstmt:   RETURN ret SEMICOLON      {
                                            std::cout << BGRN "Rule returnstmt -> ret;, line " << yylineno << RST << std::endl;
                                            $$ = Manage_returnstmt($ret);
                                        }
            ;

ret:      expr      {
                        std::cout << BGRN "Rule ret -> expr, line " << yylineno << RST << std::endl;
                        $$ = Manage_ret_expr($expr);
                    }
        |           {
                        std::cout << BGRN "Rule ret -> ε, line " << yylineno << RST << std::endl;
                        $$ = Manage_ret();
                    }
        ;
