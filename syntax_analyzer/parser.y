%{
    #include <iostream>
    #include <unordered_set>
    #include "types.h"
    #include "scope.h"
    #include "rules.h"

    int yyerror(char* yaccProvideedMessage){
        std::cerr << "Something bad happened here"<<std::endl;
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
%}

%union{

#include "types.h"
    int intValue;
    double realValue;
    programValue programVal;
    stmtListValue stmtListVal;
     stmtValue stmtVal;
     exprValue exprVal;
     termValue termVal;
     assignexprValue assignexprVal;
     primaryValue primaryVal;
     lvalueValue lvalueVal;
     memberValue memberVal;
     callValue callVal;
     callsuffixValue callsuffixVal;
     normcallValue normcallVal;
     methodcallValue methodcallVal;
     elistValue elistVal;
     exprOptRptValue exprOptRptVal;
     objectdefValue objectdefVal;
     indexedValue indexedVal;
     indelemlistValue indelemlistVal;
     indexedelemValue indexedelemVal;
     blockValue blockVal;
     funcdefValue funcdefVal;
     constValue constVal;
     idlistValue idlistVal;
    
     ifstmtValue ifstmtVal;
     elseValue elseVal;
     whilestmtValue whilestmtVal;
     forstmtValue forstmtVal;
     returnstmtValue returnstmtVal;
     retValue retVal;
    char* stringVal;
};



%token  <stringVal> ID
%token  IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE AND NOT OR LOCAL TRUE FALSE NIL
%token  ASSIGN PLUS MINUS MUL DIV MOD EQUAL NEQUAL PLUS_PLUS MINUS_MINUS GT GE LT LE
%token  <intValue> intNumber
%token  <realValue> realNumber
%token  L_CURLY_BRACKET R_CURLY_BRACKET L_SQUARE_BRACKET R_SQUARE_BRACKET L_PARENTHESIS R_PARENTHESIS SEMICOLON COMMA COLON NAMESPACE DOT DOUBLE_DOT
%token  <stringVal> STRING
%token  COMMENT
%token  BLOCK_COMMENT

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

program:      stmtList       {
                                std::cout << "\e[1;32m" "Rule program -> stmtlist" "\e[0m" << std::endl;
                                $$ = Manage_program($1);
                             }
              ;

stmtList:     stmtList stmt  {$$ = Manage_stmtList_stmt($1, $2);}
            |                {$$ = Manage_stmtList();}
            ;

stmt:     expr SEMICOLON        {$$ = Manage_stmt_expr($1);}
        | ifstmt                {$$ = Manage_stmt_ifstmt($1);}
        | whilestmt             {$$ = Manage_stmt_whilestmt($1);}
        | forstmt               {$$ = Manage_stmt_forstmt($1);}
        | returnstmt            {$$ = Manage_stmt_returnstmt($1);}
        | BREAK SEMICOLON       {$$ = Manage_stmt_break();}
        | CONTINUE SEMICOLON    {$$ = Manage_stmt_continue();}
        | block                 {$$ = Manage_stmt_block($1);}
        | funcdef               {$$ = Manage_stmt_funcdef($1);}
        | SEMICOLON             {$$ = Manage_stmt_semicolon();}
        ;

expr:     assignexpr            {$$ = Manage_expr_assignexpr($1);}
        | expr PLUS expr        {$$ = Manage_expr_expr_PLUS_expr($1, $3);}
        | expr MINUS expr       {$$ = Manage_expr_expr_MINUS_expr($1, $3);}
        | expr MUL expr         {$$ = Manage_expr_expr_MUL_expr($1, $3);}
        | expr DIV expr         {$$ = Manage_expr_expr_DIV_expr($1, $3);}
        | expr MOD expr         {$$ = Manage_expr_expr_MOD_expr($1, $3);}
        | expr GT expr          {$$ = Manage_expr_expr_GT_expr($1, $3);}
        | expr GE expr          {$$ = Manage_expr_expr_GE_expr($1, $3);}
        | expr LT expr          {$$ = Manage_expr_expr_LT_expr($1, $3);}
        | expr LE expr          {$$ = Manage_expr_expr_LE_expr($1, $3);}
        | expr EQUAL expr       {$$ = Manage_expr_expr_EQUAL_expr($1, $3);}
        | expr NEQUAL expr      {$$ = Manage_expr_expr_NEQUAL_expr($1, $3);}
        | expr AND expr         {$$ = Manage_expr_expr_AND_expr($1, $3);}
        | expr OR expr          {$$ = Manage_expr_expr_OR_expr($1, $3);}
        | term                  {$$ = Manage_expr_term($1);}
        ;

term:     L_PARENTHESIS expr R_PARENTHESIS  {
                                                std::cout << "\e[1;32m" "Rule term -> (expr)" "\e[0m" << std::endl;
                                                $$ = Manage_term_LPexprRP($2);
                                            }
        | NOT expr                          {
                                                std::cout << "\e[1;32m" "Rule term -> not expr" "\e[0m" << std::endl;
                                                $$ = Manage_term_notexpr($2);
                                            }
        | PLUS_PLUS lvalue                  {
                                                std::cout << "\e[1;32m" "Rule term -> ++lvalue" "\e[0m" << std::endl;
                                                $$ = Manage_term_PPlval($2);
                                            }
        | lvalue PLUS_PLUS                  {
                                                std::cout << "\e[1;32m" "Rule term -> lvalue++" "\e[0m" << std::endl;
                                                $$ = Manage_term_lvaluePP($1);
                                            }
        | MINUS_MINUS lvalue                {
                                                std::cout << "\e[1;32m" "Rule term -> --lvalue" "\e[0m" << std::endl;
                                                $$ = Manage_term_MMlval($2);
                                            }
        | lvalue MINUS_MINUS                {
                                                std::cout << "\e[1;32m" "Rule term -> lvalue--" "\e[0m" << std::endl;
                                                $$ = Manage_term_lvalueMM($1);
                                            }
        | primary                           {
                                                std::cout << "\e[1;32m" "Rule term -> primary" "\e[0m" << std::endl;
                                                $$ = Manage_term_primary($1);
                                            }
        | MINUS expr %prec UMINUS           {
                                                std::cout << "\e[1;32m" "Rule term -> -expr Uminus" "\e[0m" << std::endl;
                                                $$ = Manage_term_minusexpr($2);
                                            }
        ;

assignexpr: lvalue ASSIGN expr  {
                                    std::cout << "\e[1;32m" "Rule assignexpr -> lvalue=expr" "\e[0m" << std::endl;
                                    $$ = Manage_assignexpr_lvalueASSIGNexpr($1, $3);
                                }

primary:  lvalue                                {
                                                   std::cout << "\e[1;32m" "Rule primary -> lvalue" "\e[0m" << std::endl;
                                                   $$ = Manage_primary_lvalue($1);
                                                }
        | call                                  {
                                                   std::cout << "\e[1;32m" "Rule primary -> call" "\e[0m" << std::endl;
                                                   $$ = Manage_primary_call($1);
                                                }
        | objectdef                             {
                                                   std::cout << "\e[1;32m" "Rule primary -> objectdef" "\e[0m" << std::endl;
                                                   $$ = Manage_primary_objectdef($1);
                                                }
        | L_PARENTHESIS funcdef R_PARENTHESIS   {
                                                   std::cout << "\e[1;32m" "Rule primary -> (funcdef)" "\e[0m" << std::endl;
                                                   $$ = Manage_primary_LPfuncdefRP($2);
                                                }
        | const                                 {
                                                   std::cout << "\e[1;32m" "Rule primary -> const" "\e[0m" << std::endl;
                                                   $$ = Manage_primary_const($1);
                                                }
        ;

lvalue:   ID            {
                            std::cout << "\e[1;32m" "Rule lvalue -> id" "\e[0m" << std::endl;
                            $$ = Manage_lvalue_id($1);
                        }
        | LOCAL ID      {
                            std::cout << "\e[1;32m" "Rule lvalue -> local id" "\e[0m" << std::endl;
                            $$ = Manage_lvalue_localid($2);
                        }
        | NAMESPACE ID  {
                            std::cout << "\e[1;32m" "Rule lvalue -> namespace id" "\e[0m" << std::endl;
                            $$ = Manage_lvalue_globalid($2);
                        }
        | member        {
                            std::cout << "\e[1;32m" "Rule lvalue -> member" "\e[0m" << std::endl;
                            $$ = Manage_lvalue_member($1);
                        }
        ;

member:   lvalue DOT ID                                     {
                                                                std::cout << "\e[1;32m" "Rule member -> lvalue.id" "\e[0m" << std::endl;
                                                                $$ = Manage_member_lvalueDOTid($1, $3);
                                                            }
        | lvalue L_SQUARE_BRACKET expr R_SQUARE_BRACKET     {
                                                                std::cout << "\e[1;32m" "Rule member -> lvalue[expr]" "\e[0m" << std::endl;
                                                                $$ = Manage_member_lvalueLSBexprRSB($1, $3);
                                                            }
        | call DOT ID                                       {
                                                                std::cout << "\e[1;32m" "Rule member -> call.id" "\e[0m" << std::endl;
                                                                $$ = Manage_member_callDOTid($1, $3);
                                                            }
        | call L_SQUARE_BRACKET expr R_SQUARE_BRACKET       {
                                                                std::cout << "\e[1;32m" "Rule member -> call[expr]" "\e[0m" << std::endl;
                                                                $$ = Manage_member_callLSBexprRSB($1, $3);
                                                            }
        ;

call:     call L_PARENTHESIS elist R_PARENTHESIS                                        {
                                                                                            std::cout << "\e[1;32m" "Rule call -> call(elist)" "\e[0m" << std::endl;
                                                                                            $$ = Manage_call_callLPelistRP($1, $3);
                                                                                        }
        | lvalue callsuffix                                                             {
                                                                                            std::cout << "\e[1;32m" "Rule call -> lvalue callsuffix" "\e[0m" << std::endl;
                                                                                            $$ = Manage_call_lvaluecallsuffix($1, $2);
                                                                                        }
        | L_PARENTHESIS funcdef R_PARENTHESIS L_PARENTHESIS elist R_PARENTHESIS         {
                                                                                            std::cout << "\e[1;32m" "Rule call -> (funcdef)(elist)" "\e[0m" << std::endl;
                                                                                            $$ = Manage_call_LPfuncdefRPLPelistRP($2, $5);
                                                                                        }
        ;

callsuffix:   normcall      {
                                std::cout << "\e[1;32m" "Rule callsuffix -> normcall" "\e[0m" << std::endl;
                                $$ = Manage_callsuffix_normcall($1);}
            | methodcall    {
                                std::cout << "\e[1;32m" "Rule callsuffix -> methodcall" "\e[0m" << std::endl;
                                $$ = Manage_callsuffix_methodcall($1);
                            }
            ;

normcall:     L_PARENTHESIS elist R_PARENTHESIS                 {
                                                                    std::cout << "\e[1;32m" "Rule normcall -> (elist)" "\e[0m" << std::endl;
                                                                    $$ = Manage_normcall_LPelistRP($2);
                                                                }

methodcall:   DOUBLE_DOT ID L_PARENTHESIS elist R_PARENTHESIS   {
                                                                    std::cout << "\e[1;32m" "Rule methodcall -> ..id(elist)" "\e[0m" << std::endl;
                                                                    $$ = Manage_methodcall_DDOTidLPelistRP($2, $4);
                                                                }

elist:   exprOptRpt         {
                                std::cout << "\e[1;32m" "Rule elist -> exprOptRpt" "\e[0m" << std::endl;
                                $$ = Manage_elist_exprOptRpt($1);
                            }
       |                    {
                                std::cout << "\e[1;32m" "Rule elist -> ε" "\e[0m" << std::endl;
                                $$ = Manage_elist();
                            }
       ;

exprOptRpt:   expr COMMA exprOptRpt     {
                                            std::cout << "\e[1;32m" "Rule exprOptRpt -> expr,exprOptRpt" "\e[0m" << std::endl;
                                            $$ = Manage_exprOR_exprOR($1, $3);
                                        }
            | expr                      {
                                            std::cout << "\e[1;32m" "Rule exprOptRpt -> expr" "\e[0m" << std::endl;
                                            $$ = Manage_exprOR_expr($1);
                                        }
            ;

objectdef:    L_SQUARE_BRACKET elist R_SQUARE_BRACKET       {
                                                                std::cout << "\e[1;32m" "Rule objectdef -> [elist]" "\e[0m" << std::endl;
                                                                $$ = Manage_objectdef_LSBelistRSB($2);
                                                            }
            | L_SQUARE_BRACKET indexed R_SQUARE_BRACKET     {
                                                                std::cout << "\e[1;32m" "Rule objectdef -> [indexed]" "\e[0m" << std::endl;
                                                                $$ = Manage_objectdef_LSBindexedRSB($2);
                                                            }
            ;


indexed:  indelemlist   {
                            std::cout << "\e[1;32m" "Rule indexed -> indelemlist" "\e[0m" << std::endl;
                            $$ = Manage_indexed($1);
                        }
        ;

indelemlist:  indexedelem COMMA indelemlist     {
                                                    std::cout << "\e[1;32m" "Rule indelemlist -> indexedelem,indelemlist" "\e[0m" << std::endl;
                                                    $$ = Manage_indelemlist($1, $3);
                                                }
            | indexedelem                       {
                                                    std::cout << "\e[1;32m" "Rule indelemlist -> indexedelem" "\e[0m" << std::endl;
                                                    $$ = Manage_indelemlist_indexedelem($1);
                                                }
            ;


indexedelem:  L_CURLY_BRACKET expr COLON expr R_CURLY_BRACKET   {
                                                                    std::cout << "\e[1;32m" "Rule indexedelem -> {expr:expr}" "\e[0m" << std::endl;
                                                                    $$ = Manage_indexedelem_LCB_expr_COLON_expr_RCB($2, $4);
                                                                }
            ;

block:    L_CURLY_BRACKET stmtList R_CURLY_BRACKET              {$$ = Manage_block_LCBstmtRCB($2);}
        ;

funcdef:  FUNCTION ID L_PARENTHESIS idlist R_PARENTHESIS block  {
                                                                    std::cout << "\e[1;32mRule funcdef -> FUNCTION ID (idlist) block" << "id" << "\e[0m" << std::endl;
                                                                    $$ = Manage_funcdef_id($2, $4, $6);
                                                                }
        | FUNCTION L_PARENTHESIS idlist R_PARENTHESIS block     {$$ = Manage_funcdef($3, $5);}
        ;

const:    intNumber     {$$ = Manage_const_int($1);}
        | realNumber    {$$ = Manage_const_real($1);}
        | STRING        {$$ = Manage_const_string($1);}
        | NIL           {$$ = Manage_const_nil();}
        | TRUE          {$$ = Manage_const_true();}
        | FALSE         {$$ = Manage_const_false();}
        ;

idlist:   ID                {$$ = Manage_idlist_ID($1);}
        | idlist COMMA ID   {$$ = Manage_idlist_idlist_comma_id($1,$3);}
        |                   {$$ = Manage_idlist();}
        ;

ifstmt:   IF L_PARENTHESIS expr R_PARENTHESIS stmt else     {$$ = Manage_ifstmt($3, $5, $6);};

else:     ELSE stmt     {$$ = Manage_else_stmt($2);}
        |               {$$ = Manage_else();}
        ;

whilestmt:    WHILE L_PARENTHESIS expr R_PARENTHESIS stmt   {$$ = Manage_whilestmt($3,$5);}

forstmt:      FOR L_PARENTHESIS elist SEMICOLON expr SEMICOLON elist R_PARENTHESIS stmt     {$$ = Manage_for($3, $5, $7, $9);};

returnstmt:   RETURN ret SEMICOLON      {$$ = Manage_returnstmt($2);};

ret:      expr      {$$ = Manage_ret_expr($1);};
        |           {$$ = Manage_ret();}
        ;
