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

program: stmt program       {std::cout << "Program stmt program" << std::endl;}
        |
        ;

stmt:  expr SEMICOLON       {std::cout << "Stmt expr ;" << std::endl;}
        |BREAK SEMICOLON    {std::cout << "Stmt break;" << std::endl;}
        |CONTINUE SEMICOLON {std::cout << "Stmt cont;" << std::endl;}
        |funcdef            {std::cout << "Stmt func" << std::endl;}
        |SEMICOLON          {std::cout << "Stmt ;" << <std::endl;}
        ;

expr:  assignexpr          {std::cout << "Expr <-" << std::endl;}
        |expr PLUS expr       {std::cout << "Expr + expr" << std::endl;}
        |expr MINUS expr       {std::cout << "Expr - expr" << std::endl;}
        |expr MUL expr       {std::cout << "Expr * expr" << std::endl;}
        |expr DIV expr       {std::cout << "Expr * expr" << std::endl;}
        |expr MOD expr       {std::cout << "Expr * expr" << std::endl;}
        |expr GT expr       {std::cout << "Expr * expr" << std::endl;}
        |expr GE expr       {std::cout << "Expr * expr" << std::endl;}
        |expr LT expr       {std::cout << "Expr * expr" << std::endl;}
        |expr LE expr       {std::cout << "Expr * expr" << std::endl;}
        |expr EQUAL expr       {std::cout << "Expr * expr" << std::endl;}
        |expr NEQUAL expr       {std::cout << "Expr * expr" << std::endl;}
        |expr AND expr       {std::cout << "Expr * expr" << std::endl;}
        |expr OR expr       {std::cout << "Expr * expr" << std::endl;}
        |term               {std::cout << "Expr term" << std::endl;}
        ;

term: L_PARENTHESIS expr R_PARENTHESIS {std::cout << "term ( expr )" << std::endl;}
    | NOT expr                         {std::cout << "term !expr" << std::endl;}
    | PLUS_PLUS lvalue                 {std::cout << "term ++lvalue" << std::endl;}
    | lvalue PLUS_PLUS                 {std::cout << "term lvalue++" << std::endl;}
    | MINUS_MINUS lvalue               {std::cout << "term --lvalue" << std::endl;}
    | lvalue MINUS_MINUS               {std::cout << "term lvalue--" << std::endl;}
    | primary                          {std::cout << "term primary" << std::endl;}
    | MINUS expr %prec UMINUS          {std::cout << "term -expr" << std::endl;}
    ;

assignexpr :lvalue ASSIGN expr {std::cout << "assignexpr lvalue <- expr" << std::endl;}

primary : lvalue                              {std::cout << "primary lvalue" << std::endl;}
        | call                                {std::cout << "primary call" << std::endl;}
        | objectdef                           {std::cout << "primary objectdef" << std::endl;}
        | L_PARENTHESIS funcdef R_PARENTHESIS {std::cout << "primary ( funcdef )" << std::endl;}
        | const                               {std::cout << "primary const" << std::endl;}
        ;

lvalue : ID            {std::cout << "lvalue id" << std::endl;}
         |LOCAL ID     {std::cout << "lvalue local id" << std::endl;}
         |NAMESPACE ID {std::cout << "lvalue ::id" << std::endl;}
         |member       {std::cout << "lvalue member" << std::endl;}
         ;

member:  lvalue DOT ID                                   {std::cout << "member lvalue.id" << std::endl;}
       | lvalue L_SQUARE_BRACKET expr R_SQUARE_BRACKET   {std::cout << "member lvalue[expr]" << std::endl;}
       | call DOT ID                                     {std::cout << "member call.id" << std::endl;}
       | call L_SQUARE_BRACKET expr R_SQUARE_BRACKET     {std::cout << "member call [expr]" << std::endl;}
       ;

call: call L_PARENTHESIS elist R_PARENTHESIS {std::cout << "call call ( elist )" << std::endl;}
    | lvalue callsuffix                      {std::cout << "call lvalue callsuffix" << std::endl;}
    | L_PARENTHESIS funcdef R_PARENTHESIS L_PARENTHESIS elist R_PARENTHESIS        {std::cout << "call ( funcdef ) ( elist )" << std::endl;}
       ;

callsuffix :  normcall    {std::cout << "callsuffix normcall" << std::endl;}
            | methodcall {std::cout << "callsuffix methodcall" << std::endl;}
            ;

normcall : L_PARENTHESIS elist R_PARENTHESIS {std::cout << "normcall ( elist )" << std::endl;}

methodcall : DOUBLE_DOT ID L_PARENTHESIS elist R_PARENTHESIS {std::cout << "methodcall..id ( elist )" << std::endl;}

elist: exprOptRpt {std::cout << "elist ( exprOptRpt )" << std::endl;}
       ;

exprOptRpt: expr COMMA exprOptRpt {std::cout << "exprOptRpt expr , exprOptRpt" << std::endl;}
        |   expr  {std::cout << "exprOptRpt expr" << std::endl;}
        ;

objectdef: L_SQUARE_BRACKET elist R_SQUARE_BRACKET     {std::cout << "objectdef [ elist ]" << std::endl;}
        |  L_SQUARE_BRACKET indexed R_SQUARE_BRACKET {std::cout << "objectdef [ indexed ]" << std::endl;}
        |  L_SQUARE_BRACKET R_SQUARE_BRACKET          {std::cout << "objectdef [ ]" << std::endl;}
        ;


indexed : indelemlist {std::cout << "indexed indelemlist" << std::endl;}
        ;

indelemlist: indexedelem COMMA indelemlist   {std::cout << "indelemlist indexedelem , indelemlist" << std::endl;}
    | indexedelem            {std::cout << "indelemlist indexedelem" << std::endl;}
    ;


indexedelem : L_CURLY_BRACKET expr COLON expr R_CURLY_BRACKET {std::cout << "indexedelem { expr ; expr }" << std::endl;}
    ;

block:  L_CURLY_BRACKET blockStmt R_CURLY_BRACKET {std::cout << "block { blockStmt }" << std::endl;}
        ;

blockStmt: stmt blockStmt {std::cout << "blockStmt stmt blockStmt" << std::endl;}
        | {std::cout << "blockStmt empty" << std::endl;}
        ;

funcdef : FUNCTION ID L_PARENTHESIS idlist R_PARENTHESIS block  {std::cout << "funcdef function id ( idlist ) block" << std::endl;}
        | FUNCTION L_PARENTHESIS idlist R_PARENTHESIS block  {std::cout << "funcdef function ( idlist ) block" << std::endl;}

const : intNumber   {std::cout << "const int" << std::endl;}
        |realNumber {std::cout << "const real" << std::endl;}
        |STRING     {std::cout << "const string" << std::endl;}
        |NIL        {std::cout << "const nil" << std::endl;}
        |TRUE       {std::cout << "const true" << std::endl;}
        |FALSE      {std::cout << "const false" << std::endl;}
        ;

idlist : id { std::cout << "idlist" << std::endl;}
        |
         ;

id:   ID COMMA id   { std::cout << "id comma" << std::endl;}
    | ID            {std::cout << "id ID" << std::endl;}
    ;
