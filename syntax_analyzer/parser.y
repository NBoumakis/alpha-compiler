%{
    #include <iostream>
    #include "types.h"
    #include "rules.h"

    int yyerror(char* yaccProvideedMessage){
        std::cerr << "Something bad happened here"<<std::endl;
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
%token  <doubleValue> intNumber
%token  <doubleValue> realNumber
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

program:      stmtList       {std::cerr <<"Test" <<std::endl;}
              ;

stmtList:     stmtList stmt  {std::cerr << "Test" <<std::endl;}
            |                {std::cerr << "Test" <<std::endl;}
            ;

stmt:     expr SEMICOLON        {std::cerr << "Test" <<std::endl;}
        | ifstmt                {std::cerr << "Test" <<std::endl;}
        | whilestmt             {std::cerr << "Test" <<std::endl;}
        | forstmt               {std::cerr << "Test" <<std::endl;}
        | returnstmt            {std::cerr << "Test" <<std::endl;}
        | BREAK SEMICOLON       {std::cerr << "Test" <<std::endl;}
        | CONTINUE SEMICOLON    {std::cerr << "Test" <<std::endl;}
        | block                 {std::cerr << "Test" <<std::endl;}
        | funcdef               {std::cerr << "Test" <<std::endl;}
        | SEMICOLON             {std::cerr << "Test" <<std::endl;}
        ;

expr:     assignexpr            {std::cerr << "Test" <<std::endl;}
        | expr PLUS expr        {std::cerr << "Test" <<std::endl;}
        | expr MINUS expr       {std::cerr << "Test" <<std::endl;}
        | expr MUL expr         {std::cerr << "Test" <<std::endl;}
        | expr DIV expr         {std::cerr << "Test" <<std::endl;}
        | expr MOD expr         {std::cerr << "Test" <<std::endl;}
        | expr GT expr          {std::cerr << "Test" <<std::endl;}
        | expr GE expr          {std::cerr << "Test" <<std::endl;}
        | expr LT expr          {std::cerr << "Test" <<std::endl;}
        | expr LE expr          {std::cerr << "Test" <<std::endl;}
        | expr EQUAL expr       {std::cerr << "Test" <<std::endl;}
        | expr NEQUAL expr      {std::cerr << "Test" <<std::endl;}
        | expr AND expr         {std::cerr << "Test" <<std::endl;}
        | expr OR expr          {std::cerr << "Test" <<std::endl;}
        | term                  {std::cerr << "Test" <<std::endl;}
        ;

term:     L_PARENTHESIS expr R_PARENTHESIS  {std::cerr << "Test" <<std::endl;}
        | NOT expr                          {std::cerr << "Test" <<std::endl;}
        | PLUS_PLUS lvalue                  {std::cerr << "Test" <<std::endl;}
        | lvalue PLUS_PLUS                  {std::cerr << "Test" <<std::endl;}
        | MINUS_MINUS lvalue                {std::cerr << "Test" <<std::endl;}
        | lvalue MINUS_MINUS                {std::cerr << "Test" <<std::endl;}
        | primary                           {std::cerr << "Test" <<std::endl;}
        | MINUS expr %prec UMINUS           {std::cerr << "Test" <<std::endl;}
        ;

assignexpr: lvalue ASSIGN expr  {std::cerr << "Test" <<std::endl;}

primary:  lvalue                                {std::cerr << "Test" <<std::endl;}
        | call                                  {std::cerr << "Test" <<std::endl;}
        | objectdef                             {std::cerr << "Test" <<std::endl;}
        | L_PARENTHESIS funcdef R_PARENTHESIS   {std::cerr << "Test" <<std::endl;}
        | const                                 {std::cerr << "Test" <<std::endl;}
        ;

lvalue:   ID            {std::cerr << "Test" <<std::endl;}
        | LOCAL ID      {std::cerr << "Test" <<std::endl;}
        | NAMESPACE ID  {std::cerr << "Test" <<std::endl;}
        | member        {std::cerr << "Test" <<std::endl;}
        ;

member:   lvalue DOT ID                                     {std::cerr << "Test" <<std::endl;}
        | lvalue L_SQUARE_BRACKET expr R_SQUARE_BRACKET     {std::cerr << "Test" <<std::endl;}
        | call DOT ID                                       {std::cerr << "Test" <<std::endl;}
        | call L_SQUARE_BRACKET expr R_SQUARE_BRACKET       {std::cerr << "Test" <<std::endl;}
        ;

call:     call L_PARENTHESIS elist R_PARENTHESIS                                        {std::cerr << "Test" <<std::endl;}
        | lvalue callsuffix                                                             {std::cerr << "Test" <<std::endl;}
        | L_PARENTHESIS funcdef R_PARENTHESIS L_PARENTHESIS elist R_PARENTHESIS         {std::cerr << "Test" <<std::endl;}
        ;

callsuffix:   normcall      {std::cerr << "Test" <<std::endl;}
            | methodcall    {std::cerr << "Test" <<std::endl;}
            ;

normcall:     L_PARENTHESIS elist R_PARENTHESIS                 {std::cerr << "Test" <<std::endl;}

methodcall:   DOUBLE_DOT ID L_PARENTHESIS elist R_PARENTHESIS   {std::cerr << "Test" <<std::endl;}

elist:   exprOptRpt         {std::cerr << "Test" <<std::endl;}
       |                    {std::cerr << "Test" <<std::endl;}
       ;

exprOptRpt:   expr COMMA exprOptRpt     {std::cerr << "Test" <<std::endl;}
            | expr                      {std::cerr << "Test" <<std::endl;}
            ;

objectdef:    L_SQUARE_BRACKET elist R_SQUARE_BRACKET       {std::cerr << "Test" <<std::endl;}
            | L_SQUARE_BRACKET indexed R_SQUARE_BRACKET     {std::cerr << "Test" <<std::endl;}
            ;


indexed:  indelemlist   {std::cerr << "Test" <<std::endl;}
        ;

indelemlist:  indexedelem COMMA indelemlist     {std::cerr << "Test" <<std::endl;}
            | indexedelem                       {std::cerr << "Test" <<std::endl;}
            ;


indexedelem:  L_CURLY_BRACKET expr COLON expr R_CURLY_BRACKET   {std::cerr << "Test" <<std::endl;}
            ;

block:    L_CURLY_BRACKET stmtList R_CURLY_BRACKET              {std::cerr << "Test" <<std::endl;}
        ;

funcdef:  FUNCTION ID L_PARENTHESIS idlist R_PARENTHESIS block  {std::cerr << "Test" <<std::endl;}
        | FUNCTION L_PARENTHESIS idlist R_PARENTHESIS block     {std::cerr << "Test" <<std::endl;}
        ;

const:    intNumber     {std::cerr << "Test" <<std::endl;}
        | realNumber    {std::cerr << "Test" <<std::endl;}
        | STRING        {std::cerr << "Test" <<std::endl;}
        | NIL           {std::cerr << "Test" <<std::endl;}
        | TRUE          {std::cerr << "Test" <<std::endl;}
        | FALSE         {std::cerr << "Test" <<std::endl;}
        ;

idlist:   ID                {std::cerr << "Test" <<std::endl;}
        | idlist COMMA ID   {std::cerr << "Test" <<std::endl;}
        |                   {std::cerr << "Test" <<std::endl;}
        ;

ifstmt:   IF L_PARENTHESIS expr R_PARENTHESIS stmt else     {std::cerr << "Test" <<std::endl;}

else:     ELSE stmt     {std::cerr << "Test" <<std::endl;}
        |               {std::cerr << "Test" <<std::endl;}
        ;

whilestmt:    WHILE L_PARENTHESIS expr R_PARENTHESIS stmt   {std::cerr << "Test" <<std::endl;}

forstmt:      FOR L_PARENTHESIS elist SEMICOLON expr SEMICOLON elist R_PARENTHESIS stmt     {std::cerr << "Test" <<std::endl;}

returnstmt:   RETURN ret SEMICOLON      {std::cerr << "Test" <<std::endl;}

ret:      expr      {std::cerr << "Test" <<std::endl;}
        |           {std::cerr << "Test" <<std::endl;}
        ;
