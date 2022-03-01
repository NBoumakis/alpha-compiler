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

enum token_value {
   ALERT,BACKSPACE,ESCAPE,FORMFEED,NEWLINE,RETURN,
   TAB,V_TAB,Q_MARK,APOSTROPHE,DOUBLE_MARK
};

std::string enum_to_string_flex(token_value type) {
   switch(type) {
      case ALERT:
         return "\\a";
      case BACKSPACE:
         return "\\b";
      case ESCAPE:
         return "\\e";
      case FORMFEED:
         return "\\f";
      case NEWLINE:
         return "\\n";
      case RETURN:
         return "\\r";
      case TAB:
         return "\\t";
      case V_TAB:
         return "\\v";
      case Q_MARK:
         return "\\?";
      case APOSTROPHE:
         return "\\'";
      case DOUBLE_MARK:
         return "\\""";
      default:
         return "";
   }
}

std::string enum_to_result(token_value type) {
   switch(type) {
      case ALERT:
         return "\a";
      case BACKSPACE:
         return "\b";
      case ESCAPE:
         return "\e";
      case FORMFEED:
         return "\f";
      case NEWLINE:
         return "\n";
      case RETURN:
         return "\r";
      case TAB:
         return "\t";
      case V_TAB:
         return "\v";
      case Q_MARK:
         return "\?";
      case APOSTROPHE:
         return "\'";
      case DOUBLE_MARK:
         return "\"";
      default:
         return "";
   }
}

void append(struct alpha_token_t** head_ref, unsigned int numline,unsigned int numToken,std::string content, std::string type,std::string category) {
    
   struct alpha_token_t* new_node = new struct alpha_token_t();
   
    
    struct alpha_token_t *last = *head_ref;
   
    new_node->numline = numline; 
    new_node->numToken = numToken; 
    new_node->content=content;
    new_node->type=type;
    new_node->category=category;
   
    new_node->alpha_yylex = NULL; 
  
    if (*head_ref == NULL) { 
        *head_ref = new_node; 
        return; 
    } 
   
    while (last->alpha_yylex != NULL) {
        last = last->alpha_yylex; 
    }
   
    last->alpha_yylex = new_node; 
    return;
}

%}

/* Flex options */
%option noyywrap
%option yylineno

/* Flex macros */
NEW_LINE        [(\r)(\n)]

/* Identifiers */
ID              [a-zA-Z][a-zA-Z_0-9]*

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


STRING \".*(\\)*\"
SPACE [\r \t\v]
TAB [\t]
LINE_COMMENT "//".*
BLOCK_COMMENT "/*".*


%%
{NEW_LINE} { lineno++; }

{ID} { num_of_token++;  append(&yylval,lineno,num_of_token,yytext,"ID",yytext);}

{IF} {if (yyleng > 2) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"KEYWORD","IF"); } }
{ELSE} {if (yyleng > 4) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"KEYWORD","ELSE"); }}
{WHILE} {if (yyleng > 5) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"KEYWORD","WHILE"); }}
{FOR} {if (yyleng > 3) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"KEYWORD","FOR"); }}
{FUNCTION} {if (yyleng > 8) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"KEYWORD","FUNCTION"); }}
{RETURN} {if (yyleng > 6) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"KEYWORD","RETURN"); }}
{BREAK} {if (yyleng > 5) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"KEYWORD","BREAK"); }}
{CONTINUE} {if (yyleng > 8) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"KEYWORD","CONTINUE"); }}
{AND} {if (yyleng > 3) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"KEYWORD","AND"); }}
{OR} {if (yyleng > 2) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"KEYWORD","OR"); }}
{LOCAL} {if (yyleng > 5) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"KEYWORD","LOCAL"); }}
{TRUE} {if (yyleng > 4) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"KEYWORD","TRUE"); }}
{FALSE} {if (yyleng > 5) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"KEYWORD","FALSE"); }}
{NIL} {if (yyleng > 3) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"KEYWORD","NIL"); }}

{ASSIGN} {if (yyleng > 1) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","ASSIGN"); }}
{PLUS} {if (yyleng > 1) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","PLUS"); }}
{MINUS} {if (yyleng > 1) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","MINUS"); }}
{MUL} {if (yyleng > 1) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","MUL"); }}
{DIV} {if (yyleng > 1) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","DIV"); }}
{MOD} {if (yyleng > 1) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","MOD"); }}
{EQUAL} {if (yyleng > 2) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","EQUAL"); }}
{NEQUAL} {if (yyleng > 2) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","NEQUAL"); }}
{PLUS_PLUS} {if (yyleng > 2) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","PLUS_PLUS"); }}
{MINUS_MINUS} {if (yyleng > 2) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","MINUS_MINUS"); }}
{GT} {if (yyleng > 1) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","GT"); }}
{LT} {if (yyleng > 1) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","LT"); }}
{GE} {if (yyleng > 2) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","GE"); }}
{LE} {if (yyleng > 2) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"OPERATOR","LE"); }}

{CONST_INT} { num_of_token++;  append(&yylval,lineno,num_of_token,yytext,"CONST_INT",yytext);}
{CONST_REAL} { num_of_token++;  append(&yylval,lineno,num_of_token,yytext,"CONST_REAL",yytext); }

{L_CURLY_BRACKET} {if (yyleng > 1) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"PUNCTUATION","L_CURLY_BRACKET");} }
{R_CURLY_BRACKET} {if (yyleng > 1) { REJECT; } else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"PUNCTUATION","R_CURLY_BRACKET");} }
{L_SQUARE_BRACKET} {if (yyleng > 1) {REJECT;} else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"PUNCTUATION","L_SQUARE_BRACKET");} }
{R_SQUARE_BRACKET} {if (yyleng > 1) {REJECT;} else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"PUNCTUATION","R_SQUARE_BRACKET");} }
{L_PARENTHESIS} { if (yyleng > 1) {REJECT;} else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"PUNCTUATION","L_PARENTHESIS");}}
{R_PARENTHESIS} { if (yyleng > 1) {REJECT;} else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"PUNCTUATION","R_PARENTHESIS");}}
{SEMICOLON} { if (yyleng > 1) {REJECT;} else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"PUNCTUATION","SEMICOLON");}}
{COMMA} { if (yyleng > 1) {REJECT;} else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"PUNCTUATION","COMMA");}}
{COLON} { if (yyleng > 1) {REJECT;} else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"PUNCTUATION","COLON");}}
{NAMESPACE} { if (yyleng > 2) {REJECT;} else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"PUNCTUATION","NAMESPACE");}}
{DOT} { if (yyleng > 1) {REJECT;} else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"PUNCTUATION","DOT");}}
{DOUBLE_DOT} { if (yyleng > 1) {REJECT;} else { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"PUNCTUATION","DOUBLE_DOT");}}

{STRING} {      std::string a(yytext);
                size_t position;


               int i=1;
               bool error=false;
               while (i<a.size() && error==false){
                  if ((int)a[i]==92){
                     
                     if ((int)a[i+1]==92){
                        a.replace(i,2,"\\");
                     } else if ((int)a[i+1]==32){
                        a=a.substr(0,i);
                        error=true;
                     } else if (a[i+1]=='"'){
                        i++;
                     }
                      
                      if (i==a.size()-1){
                         error=true;
                      }
                   } else if (a[i]=='"'){
                     if ((i+1)!=a.size()) error=true;
                      a=a.substr(0,i+1);
                      
                   } 

                   i++;
               }

               if (error){
                  std::cout << "The string " << a << " is not terminating!" << std::endl;
               } else{
                  for (int token= (token_value::ALERT); token < (token_value::DOUBLE_MARK+1); ++token){
                     for (int i=0; i<a.size(); i++){
                        position=a.find(enum_to_string_flex(static_cast<token_value>(token)));
                        if (position != std::string::npos){
                           a.replace(position, 2, enum_to_result(static_cast<token_value>(token)));
                        }
                     }
                  }

                  num_of_token++; append(&yylval,lineno,num_of_token,a,"STRING",a);
               }
               
         } 
{SPACE} { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"SPACE",yytext); }
{TAB} { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"TAB",yytext); }
{LINE_COMMENT} { num_of_token++; append(&yylval,lineno,num_of_token,yytext,"COMMENT","LINE_COMMENT"); }
{BLOCK_COMMENT} {    std::string line(yytext);
                     
                     int open=0,close=0;
                     for (int i=0; i<line.size(); i++) {
                        if (line[i]=='/' && line[i+1]=='*'){
                           open++;
                        } else if (line[i]=='*' && line[i+1]=='/'){
                           close++;
                        }
                        i++;
                     }
                     if (open!=close){
                        std::cout << "Block comments " << line << " are not terminating!" << std::endl;
                     } else{
                        num_of_token++; append(&yylval,lineno,num_of_token,line,"COMMENT","BLOCK_COMMENT");
                     }
   
                }

%%