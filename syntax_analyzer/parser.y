%{
    #include <iostream>
    #include "../include/types.h"

    int yyerror(char* yaccProvideedMessage);


    extern int yylineno;
    extern char* yytext;


    extern int yylex();
    extern int yyparse();
    extern FILE* yyin;

    enum keywords    {IF, ELSE, WHILE, FOR, FUNCTION, RETURN, BREAK, CONTINUE, AND, NOT, OR, LOCAL, TRUE, FALSE, NIL};
    enum operator    {ASSIGN, PLUS, MINUS, MUL, DIV, MOD, EQUAL, NEQUAL, PLUS_PLUS, MINUS_MINUS, GT, GE, LT, LE};
    enum punctuation {L_CURLY_BRACKET, R_CURLY_BRACKET, L_SQUARE_BRACKET, R_SQUARE_BRACKET, L_PARENTHESIS, R_PARENTHESIS, SEMICOLON, COMMA, COLON, NAMESPACE, DOT, DOUBLE_DOT}
%}

%union{ 
    struct constValue constVal;
}



%token  <stringValue> ID
%token  IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE AND NOT OR LOCAL TRUE FALSE NIL
%token  ASSIGN PLUS MINUS MUL DIV MOD EQUAL NEQUAL PLUS_PLUS MINUS_MINUS GT GE LT LE
%token  <doubleValue> intNumber
%token  <doubleValue> realNumber
%token  L_CURLY_BRACKET R_CURLY_BRACKET L_SQUARE_BRACKET R_SQUARE_BRACKET L_PARENTHESIS R_PARENTHESIS SEMICOLON COMMA COLON NAMESPACE DOT DOUBLE_DOT
%token  <stringValue> STRING 
%token  COMMENT
%token  BLOCK_COMMENT
%token  print input objectmemberkeys objecttotalmembers objectcopy totalarguments argument strtonum sqrt cos sin

/* Non-terminal types */
%type <constVal> const

/*Associativity and priority */

%left L_PARENTHESIS R_PARENTHESIS
%left L_SQUARE_BRACKET R_SQUARE_BRACKET
%left DOT DOUBLE_DOT
%right NOT PLUS_PLUS MINUS_MINUS UMINUS
%left MUL DIV MOD
%left PLUS MINUS
%nonassoc GT GE LT LE
%nonassoc EQUAL NEQUAL
%left AND
%left OR
%right ASSIGN

%start program

%%

program: stmt program       {$$ = Manage_program($1, $2)}
        |
        ;

stmt:  expr SEMICOLON       {$$=Manage_stmt_expr($1);}
        |ifstmt             {$$=Manage_stmt_ifstmt($1);}
        |whilestmt          {$$=Manage_stmt_whilestmt($1);}
        |forstmt            {$$=Manage_stmt_forstmt($1);}
        |returnstmt         {$$=Manage_stmt_returnstmt($1);}
        |BREAK SEMICOLON    {$$=Manage_stmt_break();}
        |CONTINUE SEMICOLON {$$=Manage_stmt_continue();}
        |block              {$$=Manage_stmt_block($1);}
        |funcdef            {$$=Manage_stmt_funcdef($1);}
        |SEMICOLON
        ;

expr:  assignexpr          {$$=Manage_expr_assignexpr($1);}
        |expr op expr       {$$=Manage_expr_exprOPexpr($1, $2, $3);}
        |term               {$$=Manage_expr_term($1);}
        ;

op:   PLUS   {$$ = $1;}
    | MINUS  {$$ = $1;}
    | MUL    {$$ = $1;}
    | DIV    {$$ = $1;}
    | MOD    {$$ = $1;}
    | GT     {$$ = $1;}
    | GE     {$$ = $1;}
    | LT     {$$ = $1;}
    | LE     {$$ = $1;}
    | EQUAL  {$$ = $1;}
    | NEQUAL {$$ = $1;}
    | AND    {$$ = $1;}
    | OR     {$$ = $1;}
    ;

term: L_PARENTHESIS expr R_PARENTHESIS {$$ = Manage_term_LPexprRP($2);}
    | NOT expr                         {$$ = Manage_term_notexpr($2);}
    | PLUS_PLUS lvalue                 {$$ = Manage_term_PPlval($2);}
    | lvalue PLUS_PLUS                 {$$ = Manage_term_lvaluePP($1);}
    | MINUS_MINUS lvalue               {$$ = Manage_term_MMlval($2);}
    | lvalue MINUS_MINUS               {$$ = Manage_term_lvalueMM($1);}
    | primary                          {$$ = Manage_term_primary($1);}
    | MINUS expr %prec UMINUS          {$$ = Manage_term_minusexpr($2);}
    ;

assignexpr :lvalue ASSIGN expr {$$=Manage_assignexpr_lvalueASSIGNexpr($1, $3);}

primary : lvalue                              {$$ = Manage_primary_lvalue($1);}
        | call                                {$$ = Manage_primary_call($1);}
        | objectdef                           {$$ = Manage_primary_objectdef($1);}
        | L_PARENTHESIS funcdef R_PARENTHESIS {$$ = Manage_primary_LPfuncdefRP($2);}
        | const                               {$$ = Manage_primary_const($1);}
        ;

lvalue : ID            {$$=Manage_lvalue_id($1);}
         |LOCAL ID     {$$=Manage_lvalue_localid($2);}
         |NAMESPACE ID {$$=Manage_lvalue_globalid($2);}
         |member       {$$=Manage_lvalue_member($1);}
         ;

member:  lvalue DOT ID                                   {$$=Manage_member_lvalueDOTid($1, $3);}
       | lvalue L_SQUARE_BRACKET expr R_SQUARE_BRACKET   {$$=Manage_member_lvalueLSBexprRSB($1, $3);}
       | call DOT ID                                     {$$=Manage_member_callDOTid($1, $3);}
       | call L_SQUARE_BRACKET expr R_SQUARE_BRACKET {$$=Manage_member_calLSBexprRSB($1, $3);}
       ;

call: call L_PARENTHESIS elist R_PARENTHESIS {$$ = Manage_call_callLPelistRP($1, $3);}
    | lvalue callsuffix                      {$$ = Manage_call_lvaluecallsuffix($1, $2);}
    | L_PARENTHESIS funcdef R_PARENTHESIS L_PARENTHESIS elist R_PARENTHESIS        {$$ = Manage_call_LPfuncdefRPLPelistRP($2, $5);}
       ;

callsuffix :  normcall    {$$=Manage_callsuffix_normcall($1);}
            | methodcall {$$=Manage_callsuffix_methodcall($1);}
            ;

normcall : L_PARENTHESIS elist R_PARENTHESIS {$$=Manage_normcall_LPelistRP($2);}

methodcall : DOUBLE_DOT ID L_PARENTHESIS elist R_PARENTHESIS {$$=Manage_methodcall_DDOTidLPelistRP($2, $4);}

elist: exprOptRpt {$$ = Manage_elist_exprCOMMAexpr($1);}
       |
       ;

exprOptRpt: expr COMMA exprOptRpt {$$ = Manage_exprOR_exprOR($1, $3);}
        |   expr  {$$ = $1;}
        ;

objectdef: L_SQUARE_BRACKET elist R_SQUARE_BRACKET     {$$=Manage_objectdef_LSBelistRSB($2);}
        |  L_SQUARE_BRACKET indexed R_SQUARE_BRACKET {$$=Manage_objectdef_LSBindexedRSB($2);}
        |  L_SQUARE_BRACKET R_SQUARE_BRACKET          {$$=Manage_objectdef_LSBRSB();}
        ;


indexed : indelemlist {$$=Manage_indexed($1);}
        |
        ;

indelemlist: indexedelem COMMA indelemlist   {$$ = Manage_indelemlist($1, $3)}
    | indexedelem            {$$ = $1}
    ;


indexedelem : L_CURLY_BRACKET expr COLON expr R_CURLY_BRACKET {$$ = Manage_indexedelem_LCB_expr_COLON_expr_RCB($2, $4);};

block:  L_CURLY_BRACKET blockStmt R_CURLY_BRACKET {$$=Manage_block_LCBstmtRCB($2);}
        ;

blockStmt: stmt blockStmt {$$ = Manage_blockStmt($1, $2);}
        |
        ;

funcdef : FUNCTION ID L_PARENTHESIS idlist R_PARENTHESIS block  {$$ = Manage_funcdef_id($2, $4, $6);}
        | FUNCTION L_PARENTHESIS idlist R_PARENTHESIS block  {$$=Manage_funcdef($3, $5);}

const : intNumber   {$$ = $1;}
        |realNumber {$$ = $1;}
        |STRING     {$$ = $1;}
        |NIL        {$$ = null;}
        |TRUE       {$$ = true;}
        |FALSE      {$$ = false;}
        ;

idlist : id {$$ = Manage_idlist($1);}
        |
         ;

id:   ID COMMA id   {$$ = Manage_multiple_id($1, $3)}
    | ID            {$$ = $1}
    ;

ifstmt : IF L_PARENTHESIS expr R_PARENTHESIS stmt else {$$=Manage_ifstmt($3, $5);};

else : ELSE stmt {$$ = Manage_else($2);}
    | ;

whilestmt : WHILE L_PARENTHESIS expr R_PARENTHESIS stmt {$$=Manage_whilestmt($3,$5);}

forstmt : FOR L_PARENTHESIS elist SEMICOLON expr SEMICOLON elist R_PARENTHESIS stmt {$$=Manage_for($3, $5, $7, $9);};

returnstmt : RETURN ret {$$=Manage_returnstmt($2);};

ret : expr
     | ;
