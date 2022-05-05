%{
    #include <iostream>
    #include <unordered_set>
    #include <stack>
    #include <string.h>
    #include "types.h"
    #include "icode.h"
    #include "scope.h"
    #include "symbol.h"
    #include "symbol_table.h"

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
%}

%union{

#include "types.h"
    int intValue;
    double realValue;
    programValue *programVal;
    stmtListValue *stmtListVal;
    stmtValue *stmtVal;
    exprValue *exprVal;
    exprOptRptValue *exprOptRptVal;
    primaryValue *primaryVal;
    callValue *callVal;
    blockValue *blockVal;
    unsigned long ulongVal;
    idlistValue *idlistVal;

    forprefixValue *forprefixVal;
    returnstmtValue *returnstmtVal;
    retValue *retVal;
    char* stringVal;
    Symbol* symPointer;
    Function *funcPointer;
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
%type <exprVal> term
%type <exprVal> assignexpr
%type <exprVal> primary
%type <exprVal> lvalue
%type <exprVal> member
%type <exprVal> call
%type <exprVal> objectdef
%type <exprVal> elist
%type <callVal> callsuffix
%type <callVal> normcall
%type <callVal> methodcall
%type <exprVal> exprOptRpt
%type <exprOptRptVal> indexed
%type <exprOptRptVal> indexedelem
%type <blockVal> block

%type <stringVal> funcname
%type <funcPointer> funcprefix
%type <ulongVal> funcbody
%type <funcPointer> funcdef
%type <exprVal> const
%type <idlistVal> idlist

%type <ulongVal> ifprefix
%type <ulongVal> elseprefix
%type <stmtVal>  loopstmt
%type <ulongVal> whilestart
%type <ulongVal> whilecond
%type <ulongVal> m n
%type <forprefixVal> forprefix
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
                                    $$ = Manage_stmt_ifstmt();
                                }
        | while             {
                                    std::cout << BGRN "Rule stmt -> while, line " << yylineno << RST << std::endl;
                                    $$ = Manage_stmt_whilestmt();
                                }
        | for               {
                                    std::cout << BGRN "Rule stmt -> for, line " << yylineno << RST << std::endl;
                                    $$ = Manage_stmt_for();
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
                                            $$ = Manage_expr_expr_GE_expr($left, $right);
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
                                            $$ = Manage_expr_term($term);
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

exprOptRpt:   exprOptRpt[derivated] COMMA expr  {
                                                    std::cout << BGRN "Rule exprOptRpt -> expr, exprOptRpt, line " << yylineno << RST << std::endl;
                                                    $$ = Manage_exprOptRpt_expr_exprOptRpt($expr, $derivated);
                                                }
            | expr                              {
                                                    std::cout << BGRN "Rule exprOptRpt -> expr, line " << yylineno << RST << std::endl;
                                                    $$ = Manage_exprOptRpt_expr($expr);
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


indexed:      indexedelem COMMA indexed[derivated]  {
                                                            std::cout << BGRN "Rule indelemlist -> indexedelem, indelemlist, line " << yylineno << RST << std::endl;
                                                            $$ = Manage_indexed_indexedelem_COMMA_indexed($indexedelem, $derivated);
                                                        }
            | indexedelem                               {
                                                            std::cout << BGRN "Rule indelemlist -> indexedelem, line " << yylineno << RST << std::endl;
                                                            $$ = Manage_indexed_indexedelem($indexedelem);
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

funcblockstart: {
                    loopcounterstack.push(loopcounter);
                    loopcounter = 0;
                }
            ;

funcblockend:   {
                    loopcounter =loopcounterstack.top();
                    loopcounterstack.pop();
                }
            ;

funcbody: funcblockstart block funcblockend
    {
        std::cout << BGRN "Rule funcbody -> block, line " << yylineno << RST << std::endl;

        $$ = Manage_funcbody();
        --funcDepth;
    }
            ;

funcdef:  funcprefix funcargs funcbody
            {
                std::cout << BGRN "Rule funcdef -> funcprefix funcargs funcbody, line " << yylineno << RST << std::endl;
                Manage_funcdef($funcprefix, $funcbody);
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

ifprefix: IF L_PARENTHESIS expr R_PARENTHESIS   {
                                                    std::cout << BGRN "Rule ifprefix -> if (expr) stmt else, line " << yylineno << RST << std::endl;
                                                    $$ = Manage_ifprefix($expr);
                                                }

ifstmt:   ifprefix stmt {
                            std::cout << BGRN "Rule ifstmt -> if (expr) stmt else, line " << yylineno << RST << std::endl;
                            Manage_ifstmt_ifprefix_stmt($ifprefix, $stmt);
                        }
        | ifprefix stmt[true_stmt] elseprefix stmt[false_stmt]
                        {
                            std::cout << BGRN "Rule ifstmt -> ifprefix stmt elseprefix stmt, line " << yylineno << RST << std::endl;
                            Manage_ifstmt_ifprefix_stmt_else_prefix_stmt($ifprefix, $elseprefix);
                        }
        ;

elseprefix:   ELSE  {
                        std::cout << BGRN "Rule elseprefix -> else stmt, line " << yylineno << RST << std::endl;
                        $$ = Manage_elseprefix();
                    }
            ;

loopstart:  {
                std::cout << BGRN "Rule loopstart -> ε, line " << yylineno << RST << std::endl;
                ++loopcounter;
            }
        ;


loopend:    {
                std::cout << BGRN "Rule loopend -> ε, line " << yylineno << RST << std::endl;
                --loopcounter;
            }
        ;

loopstmt: loopstart stmt loopend    {
                                        std::cout << BGRN "Rule loopstmt -> loopstart stmt loopend, line " << yylineno << RST << std::endl;
                                        $loopstmt = $stmt;
                                    }

whilestart: WHILE   {
                        std::cout << BGRN "Rule whilestart -> WHILE, line " << yylineno << RST << std::endl;
                        $$ = Manage_whilestart();
                    }

whilecond:  L_PARENTHESIS expr R_PARENTHESIS
                    {
                        std::cout << BGRN "Rule whilecond -> ( expr ), line " << yylineno << RST << std::endl;
                        $$ = Manage_whilecond($expr);
                    }

while:    whilestart whilecond loopstmt
                    {
                        std::cout << BGRN "Rule while -> whilestart whilecond loopstmt, line " << yylineno << RST << std::endl;
                        Manage_while($whilestart, $whilecond, $loopstmt);
                    }
        ;

n:  {
        std::cout << BGRN "Rule n -> ε, line " << yylineno << RST << std::endl;
        $$ = Manage_n();
    }
    ;

m:  {
        std::cout << BGRN "Rule m -> ε, line " << yylineno << RST << std::endl;
        $$ = Manage_m();
    }
    ;

forprefix:  FOR L_PARENTHESIS elist SEMICOLON m expr SEMICOLON
    {
        std::cout << BGRN "Rule forprefix -> for( elist; m expr; , line " << yylineno << RST << std::endl;
        $forprefix = Manage_forprefix($m, $expr);
    }

for:  forprefix n[n1] elist R_PARENTHESIS n[n2] loopstmt n[n3]
    {
        std::cout << BGRN "Rule for -> forprefix n1 elist ) n2 loopstmt n3, line " << yylineno << RST << std::endl;
        Manage_for($forprefix, $n1, $n2, $n3,$loopstmt);
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
