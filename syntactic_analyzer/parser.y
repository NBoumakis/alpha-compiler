%{  
    int yylex();   
    void yyerror(char* yaccProvideMessage);
    #include <iostream>
    #include <stdlib.h>
    #include <fstream>
 
    int symbols[52];
    int symbolVal(char symbol);
    void updateSymbolVal(char symbol, int value);

    extern int yylineno;
    extern char *yytext;
    extern FILE *yyin;
%}

/* store in union the value of the token */
%union{ char id; int intValue; double realValue; char* stringValue; }

%start program

/*token from scanner.l file */
%token <stringValue> ID
%token IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE AND NOT OR LOCAL TRUE FALSE NIL
%token ASSIGN PLUS MINUS MUL DIV MOD EQUAL NEQUAL PLUS_PLUS MINUS_MINUS GT GE LT LE
%token <doubleValue> intNumber
%token <doubleValue> realNumber
%token L_CURLY_BRACKET R_CURLY_BRACKET L_SQUARE_BRACKET R_SQUARE_BRACKET L_PARENTHESIS R_PARENTHESIS SEMICOLON COMMA COLON NAMESPACE DOT DOUBLE_DOT
%token <stringValue> STRING 
%token <stringValue> COMMENT
%token <stringValue> BLOCK_COMMENT

/* library functions */
%token print input objectmemberkeys objecttotalmembers objectcopy totalarguments argument strtonum sqrt cos sin

/* type of grammar expressions */
%type <intValue> stmt expr term
%type <id> assignexpr

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

%%

program: stmt'*'

stmt: expr ';' {;}
      | BREAK ';' {;}
      | CONTINUE ';' {;}
      | ';' {;}

expr: assignexpr {;}
      | expr op expr { $$ = $1 op $3; }
      | term

op: PLUS | MINUS | MUL | DIV | MOD | GT | GE | LT | LE | EQUAL | NEQUAL | AND | OR

term: L_PARENTHESIS expr R_PARENTHESIS { $$ = L_PARENTHESIS $2 R_PARENTHESIS; }
      | UMINUS expr { $$ = UMINUS $2; }
      | NOT expr { $$ = NOT $2; }
      | PLUS_PLUS lvalue
      | lvalue PLUS_PLUS
      | MINUS_MINUS lvalue
      | lvalue MINUS_MINUS
      | primary

assignexpr: lvalue '=' expr { symbols[$1] = $3; }

primary: lvalue

lvalue: ID ';' { $$ = symbols[$1]; }
%%

void yyerror(char* yaccProvideMessage){
    std::cerr << yaccProvideMessage << " at line " << yylineno << " before token " << yytext << std::endl;
    std::cerr << "INPUT NOT VALID\n";
}

int main(int argc, char **argv) {
    std::ofstream outfile;

    if (argc > 1) {
        if (!(yyin = fopen(argv[1], "r"))) {
            std::cerr << "Cannot read file: " << argv[1] << std::endl;
            return -1;
        }
    } else {
        yyin = stdin;
    }

    if (argc > 2) {
        outfile.open(argv[2]);
        if (!(outfile.is_open())) {
            std::cerr << "Cannot open output file: " << argv[2] << std::endl;
            return -1;
        }
    }

    std::ostream &out = (argc > 2) ? outfile : std::cout;

    for (int i=0; i<52; i++){
        symbols[i]=0;
    }

    yyparse();

    return 0;
}
