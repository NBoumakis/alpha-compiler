%{
#include <iostream>
#include <string>
#include <list>


struct alpha_token_t {
  unsigned int     numline;
  unsigned int     numToken;
  std::string       content;
  std::string      type;
  std::string      category;
  struct alpha_token_t *alpha_yylex;

};

struct alpha_token_t* yylval;
unsigned int num_of_token = 0;
unsigned int lineno=1;
enum Keyword{IF,ELSE};


void append(struct alpha_token_t** head_ref, unsigned int numline,unsigned int numToken,std::string content, std::string type,std::string category)
{
    
   struct alpha_token_t* new_node = new struct alpha_token_t();
   
    
    struct alpha_token_t *last = *head_ref;
   
    new_node->numline = numline; 
    new_node->numToken = numToken; 
    new_node->content=content;
    new_node->type=type;
    new_node->category=category;
   
    new_node->alpha_yylex = NULL; 
  
    if (*head_ref == NULL) 
    { 
        *head_ref = new_node; 
        return; 
    } 
   
    while (last->alpha_yylex != NULL)
    {
        last = last->alpha_yylex; 
    }
   
    last->alpha_yylex = new_node; 
    return;
}
%}

/* Flex options */
%option noyywrap

/* Flex macros */
NEW_LINE        [(\r)(\n)]
/* Keywords */
IF              "if"
ELSE            "else"
WHILE           "while"
FOR             "for"
FUNCTION        "function"
RETURN          "return"
BREAK           "break"
CONTINUE        "continue"
AND             "and"
NOT             "not"
OR              "or"
LOCAL           "local"
TRUE            "true"
FALSE           "false"
NIL             "nil"

/* Operators */
ASSIGN          "="
PLUS            "+"
MINUS           "-"
MUL             "*"
DIV             "/"
MOD             "%"
EQUAL           "=="
NEQUAL          "!="
PLUS_PLUS       "++"
MINUS_MINUS     "--"
GT              ">"
LT              "<"
GE              ">="
LE              "<="

/* Identifiers */
ID              [a-zA-Z][a-zA-Z_0-9]*

/* Integers */
CONST_REAL      ([0-9]+)\.([0-9]+)
CONST_INT       ([0-9]+)


/* Punctuation */
L_CURLY_BRACKET     "{"
R_CURLY_BRACKET     "}"
L_SQUARE_BRACKET    "["
R_SQUARE_BRACKET    "]"
L_PARENTHESIS       "("
R_PARENTHESIS       ")"
SEMICOLON           ";"
COMMA               ","
COLON               ":"
NAMESPACE           "::"
DOT                 "."
DOUBLE_DOT          ".."


STRING \"(.)*\"
COMMENT "//".*
SPACE [\r ]
TAB   [\t]


%%

{NEW_LINE} {lineno++;;}

{IF} {if (yyleng > 2) {REJECT;} else {num_of_token++ ; append(&yylval,lineno,num_of_token,yytext,"KEYWORD","IF"); } }
{ELSE} {if (yyleng > 4) {REJECT;} else {num_of_token++ ; append(&yylval,lineno,num_of_token,yytext,"KEYWORD","ELSE"); }}
{WHILE} {if (yyleng > 5) {REJECT;} else {num_of_token++ ; append(&yylval,lineno,num_of_token,yytext,"KEYWORD","WHILE"); }}
{FOR} {if (yyleng > 3) {REJECT;} else {num_of_token++ ; append(&yylval,lineno,num_of_token,yytext,"KEYWORD","FOR"); }}
{FUNCTION} {if (yyleng > 8) {REJECT;} else {num_of_token++ ; append(&yylval,lineno,num_of_token,yytext,"KEYWORD","FUNCTION"); }}
{RETURN} {if (yyleng > 6) {REJECT;} else {num_of_token++ ; append(&yylval,lineno,num_of_token,yytext,"KEYWORD","RETURN"); }}
{BREAK} {if (yyleng > 5) {REJECT;} else {num_of_token++ ; append(&yylval,lineno,num_of_token,yytext,"KEYWORD","BREAK"); }}
{CONTINUE} {if (yyleng > 8) {REJECT;} else {num_of_token++ ; append(&yylval,lineno,num_of_token,yytext,"KEYWORD","CONTINUE"); }}
{AND} {if (yyleng > 3) {REJECT;} else {num_of_token++ ; append(&yylval,lineno,num_of_token,yytext,"KEYWORD","AND"); }}
{OR} {if (yyleng > 2) {REJECT;} else {num_of_token++ ; append(&yylval,lineno,num_of_token,yytext,"KEYWORD","OR"); }}
{LOCAL} {if (yyleng > 5) {REJECT;} else {num_of_token++ ; append(&yylval,lineno,num_of_token,yytext,"KEYWORD","LOCAL"); }}
{NIL} {if (yyleng > 3) {REJECT;} else {num_of_token++ ; append(&yylval,lineno,num_of_token,yytext,"KEYWORD","NIL"); }}

{ASSIGN} {if (yyleng > 1) {REJECT;} else {num_of_token++ ; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","ASSIGN"); }}
{PLUS} {if (yyleng > 1) {REJECT;} else {num_of_token++ ; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","PLUS"); }}
{MINUS} {if (yyleng > 1) {REJECT;} else {num_of_token++ ; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","MINUS"); }}
{MUL} {if (yyleng > 1) {REJECT;} else {num_of_token++ ; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","MUL"); }}
{DIV} {if (yyleng > 1) {REJECT;} else {num_of_token++ ; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","DIV"); }}
{MOD} {if (yyleng > 1) {REJECT;} else {num_of_token++ ; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","MOD"); }}
{EQUAL} {if (yyleng > 2) {REJECT;} else {num_of_token++ ; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","EQUAL"); }}
{NEQUAL} {if (yyleng > 2) {REJECT;} else {num_of_token++ ; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","NEQUAL"); }}
{PLUS_PLUS} {if (yyleng > 2) {REJECT;} else {num_of_token++ ; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","PLUS_PLUS"); }}
{MINUS_MINUS} {if (yyleng > 2) {REJECT;} else {num_of_token++ ; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","MINUS_MINUS"); }}
{GT} {if (yyleng > 1) {REJECT;} else {num_of_token++ ; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","GT"); }}
{LT} {if (yyleng > 1) {REJECT;} else {num_of_token++ ; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","LT"); }}
{GE} {if (yyleng > 2) {REJECT;} else {num_of_token++ ; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","GE"); }}
{LE} {if (yyleng > 2) {REJECT;} else {num_of_token++ ; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","LE"); }}

{ID} { num_of_token++ ;  append(&yylval,lineno,num_of_token,yytext,"ID",yytext);}

{CONST_INT} { num_of_token++ ;  append(&yylval,lineno,num_of_token,yytext,"CONST_INT",yytext);}
{CONST_REAL} {num_of_token++ ;  append(&yylval,lineno,num_of_token,yytext,"CONST_REAL",yytext); }

{L_CURLY_BRACKET} {if (yyleng > 1) {REJECT;} else {num_of_token++ ;append(&yylval,lineno,num_of_token,yytext,"PUNCTUATION","L_CURLY_BRACKET");} }
{R_CURLY_BRACKET} {if (yyleng > 1) {REJECT;} else {num_of_token++ ;append(&yylval,lineno,num_of_token,yytext,"PUNCTUATION","R_CURLY_BRACKET");} }
{L_SQUARE_BRACKET} {if (yyleng > 1) {REJECT;} else {num_of_token++ ;append(&yylval,lineno,num_of_token,yytext,"PUNCTUATION","L_SQUARE_BRACKET");} }
{R_SQUARE_BRACKET} {if (yyleng > 1) {REJECT;} else {num_of_token++ ;append(&yylval,lineno,num_of_token,yytext,"PUNCTUATION","R_SQUARE_BRACKET");} }
{L_PARENTHESIS} { if (yyleng > 1) {REJECT;} else {num_of_token++ ;append(&yylval,lineno,num_of_token,yytext,"PUNCTUATION","L_PARENTHESIS");}}
{R_PARENTHESIS} { if (yyleng > 1) {REJECT;} else {num_of_token++ ;append(&yylval,lineno,num_of_token,yytext,"PUNCTUATION","R_PARENTHESIS");}}
{SEMICOLON} { if (yyleng > 1) {REJECT;} else {num_of_token++ ;append(&yylval,lineno,num_of_token,yytext,"PUNCTUATION","SEMICOLON");}}
{COMMA} { if (yyleng > 1) {REJECT;} else {num_of_token++ ;append(&yylval,lineno,num_of_token,yytext,"PUNCTUATION","COMMA");}}
{COLON} { if (yyleng > 1) {REJECT;} else {num_of_token++ ;append(&yylval,lineno,num_of_token,yytext,"PUNCTUATION","COLON");}}
{NAMESPACE} { if (yyleng > 2) {REJECT;} else {num_of_token++ ;append(&yylval,lineno,num_of_token,yytext,"PUNCTUATION","NAMESPACE");}}
{DOT} { if (yyleng > 1) {REJECT;} else {num_of_token++ ;append(&yylval,lineno,num_of_token,yytext,"PUNCTUATION","DOT");}}
{DOUBLE_DOT} { if (yyleng > 1) {REJECT;} else {num_of_token++ ;append(&yylval,lineno,num_of_token,yytext,"PUNCTUATION","DOUBLE_DOT");}}

{STRING}  { num_of_token++ ;append(&yylval,lineno,num_of_token,yytext,"STRING",yytext);}
 



%%

