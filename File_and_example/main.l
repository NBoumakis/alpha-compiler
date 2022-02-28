%{
#include <iostream>
#include <string>

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

%}

/* Flex options */
%option noyywrap
%option yylineno

/* Flex macros */
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
LINE_COMMENT "//".*
SPACE [\r \t\v]
BLOCK_COMMENT "/*".*


%%
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

                  std::cout << "Recognised STRING with value: " << a << std::endl; 

               }
               
         } 

{IF}/[^a-zA-Z] { std::cout << "Recognised IF with value: "<< yytext <<std::endl; } 
{ID} { std::cout << "Recognised ID with value: "<< yytext <<std::endl; }
{EQUAL} { std::cout << "Recognised OPERATOR EQUAL with value: "<< yytext <<std::endl; }
{ASSIGN} { std::cout << "Recognised OPERATOR ASSIGNN with value: "<< yytext <<std::endl; }
{CONST_REAL} { std::cout << "Recognised CONST_REAL with value: " << yytext << std::endl; }
{CONST_INT} { std::cout << "Recognised CONST_INT with value: " << yytext << std::endl; }
{LINE_COMMENT} { std::cout << "Recognised LINE_COMMENT with value: " << yytext << std::endl; }

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
                        std::cout << "Recognised BLOCK_COMMENT with value: " << line << std::endl; 
                     }
   
                }
{SPACE} { std::cout << "Recognised SPACE with value: " << yytext << std::endl; }


%%

int main(int argc, char** argv){
    if (argc > 1){
        if (!(yyin = fopen(argv[1], "r"))){
            fprintf(stderr, "Cannot read file: %s\n", argv[1]);
            return -1;
        }
    } else{
        yyin = stdin;
    }
    yylex();
    return 0;
}