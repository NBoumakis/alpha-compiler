%{
#include <iostream>
#include <string>
#include <stack>
#include "scanner.h"

#define YY_DECL int alpha_yylex(void *yylval)

std::list<alpha_token_t *> token_list;

int string_line_start;
%}

/* Flex options */
%option noyywrap
%option yylineno

%x str
%x multi_cmnt

/* Flex macros */
/* Keywords */
ID              [a-zA-Z][a-zA-Z_0-9]*

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


/* Integers */
CONST_INT       ([0-9]+)
CONST_REAL      ([0-9]+)\.([0-9])+

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

STRING \"
COMMENT "//".*
SPACE [\r \t\v]

%%
    char string_buf[YY_BUF_SIZE];
    char *string_buf_ptr;



{IF} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "KEYWORD IF <-enumerated");
    token->add_token_to_list();
} 

{ELSE} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "KEYWORD ELSE <-enumerated");
    token->add_token_to_list();
}

{WHILE} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "KEYWORD WHILE <-enumerated");
    token->add_token_to_list();
}

{FOR} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "KEYWORD FOR <-enumerated");
    token->add_token_to_list();
} 

{FUNCTION} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "KEYWORD FUNCTION <-enumerated");
    token->add_token_to_list();
}

{RETURN} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "KEYWORD RETURN <-enumerated");
    token->add_token_to_list();
}

{BREAK} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "KEYWORD BREAK <-enumerated");
    token->add_token_to_list();
}

{CONTINUE} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "KEYWORD CONTINUE <-enumerated");
    token->add_token_to_list();
}

{AND} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "KEYWORD AND <-enumerated");
    token->add_token_to_list();
}

{NOT} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "KEYWORD NOT <-enumerated");
    token->add_token_to_list();
}

{OR} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "KEYWORD OR <-enumerated");
    token->add_token_to_list();
}

{LOCAL} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "KEYWORD LOCAL <-enumerated");
    token->add_token_to_list();
}

{TRUE} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "KEYWORD TRUE <-enumerated");
    token->add_token_to_list();
}

{FALSE} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "KEYWORD FALSE <-enumerated");
    token->add_token_to_list();
}

{NIL} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "KEYWORD NIL <-enumerated");
    token->add_token_to_list();
}





{ASSIGN} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "OPERATOR ASSIGN <-enumerated");
    token->add_token_to_list();
}

{PLUS} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "OPERATOR PLUS <-enumerated");
    token->add_token_to_list();
}

{MINUS} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "OPERATOR MINUS <-enumerated");
    token->add_token_to_list();
}

{MUL} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "OPERATOR MUL<-enumerated");
    token->add_token_to_list();
}

{DIV} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "OPERATOR DIV <-enumerated");
    token->add_token_to_list();
}

{MOD} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "OPERATOR MOD <-enumerated");
    token->add_token_to_list();
}

{EQUAL} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "OPERATOR EQUAL <-enumerated");
    token->add_token_to_list();
}

{NEQUAL} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "OPERATOR NEQUAL <-enumerated");
    token->add_token_to_list();
}

{PLUS_PLUS} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "OPERATOR PLUS_PLUS <-enumerated");
    token->add_token_to_list();
}

{MINUS_MINUS} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "OPERATOR MINUS_MINUS <-enumerated");
    token->add_token_to_list();
}

{GT} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "OPERATOR GT <-enumerated");
    token->add_token_to_list();
}

{LT} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "OPERATOR LT <-enumerated");
    token->add_token_to_list();
}

{GE} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "OPERATOR GE <-enumerated");
    token->add_token_to_list();
}

{LE} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "OPERATOR LE <-enumerated");
    token->add_token_to_list();
}



{CONST_INT} {
    std::string type = "CONST_INT ";
    type.append(yytext);
    type.append(" <-integer");

    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), type);
    token->add_token_to_list();
}

{CONST_REAL} {
    std :: string type = "CONST_REAL ";
    type.append(yytext);
    type.append(" <-real");

    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), type);
    token->add_token_to_list();
}



{L_CURLY_BRACKET} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "PUNCTUATION L_CURLY_BRACKET  <-enumerated");
    token->add_token_to_list();
}

{R_CURLY_BRACKET} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "PUNCTUATION R_CURLY_BRACKET  <-enumerated");
    token->add_token_to_list();
}

{L_SQUARE_BRACKET} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "PUNCTUATION L_SQUARE_BRACKET  <-enumerated");
    token->add_token_to_list();
}

{R_SQUARE_BRACKET} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "PUNCTUATION R_SQUARE_BRACKET  <-enumerated");
    token->add_token_to_list();
}

{L_PARENTHESIS} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "PUNCTUATION L_PARENTHESIS  <-enumerated");
    token->add_token_to_list();
}

{R_PARENTHESIS} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "PUNCTUATION R_PARENTHESIS  <-enumerated");
    token->add_token_to_list();
}

{SEMICOLON} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "PUNCTUATION SEMICOLON <-enumerated");
    token->add_token_to_list();
}

{COMMA} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "PUNCTUATION COMMA  <-enumerated");
    token->add_token_to_list();
}

{COLON} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "PUNCTUATION COLON  <-enumerated");
    token->add_token_to_list();
}

{NAMESPACE} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "PUNCTUATION NAMESPACE  <-enumerated");
    token->add_token_to_list();
}

{DOT} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "PUNCTUATION DOT  <-enumerated");
    token->add_token_to_list();
}

{DOUBLE_DOT} {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "PUNCTUATION DOUBLE_DOT  <-enumerated");
    token->add_token_to_list();
}

{ID} {
    std :: string type = "ID \"";
    type.append(yytext);
    type.append("\" <-char*");

    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), type);
    token->add_token_to_list();
}



\"      {
            string_buf_ptr = string_buf;
            string_line_start = yyget_lineno(); 
            BEGIN(str);
        }
\n {}

{SPACE} {}

<str>\"        { /* saw closing quote - all done */
            BEGIN(INITIAL);
            *string_buf_ptr = '\0';
        
            std :: string type = "STRING \"";
            type.append(string_buf);
            type.append("\" <-char*");
            alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
            token = new alpha_token_t(string_line_start, token_list.size()+1, std::string(string_buf), type);
            token->add_token_to_list();
            }

<str>\\n  *string_buf_ptr++ = '\n';
<str>\\t  *string_buf_ptr++ = '\t';
<str>\\\"  *string_buf_ptr++ = '"';

<str>\\(.|\n)  *string_buf_ptr++ = yytext[1];

<str>[^\\\"]+        {
                char *yptr = yytext;

                while ( *yptr )
                    *string_buf_ptr++ = *yptr++;
            }
    
<str><<EOF>> {
    std::cout << "EOF in string\n";
    BEGIN(INITIAL);
}

"/*"        {
                std::stack<int> cmnt_start_line;
                cmnt_start_line.push(yyget_lineno());

                int c;
                while (c=yyinput()) {
                    if (c=='*') {
                        if ((c=yyinput())=='/') {
                            int start_line = cmnt_start_line.top();
                            alpha_token_t *token = static_cast<alpha_token_t *>(yylval);

                            std::string content = std::to_string(start_line) + " - " + std::to_string(yyget_lineno());
                            if (cmnt_start_line.size()==1) {
                                std::string type = "COMMENT BLOCK_COMMENT <-enumerated";

                                token = new alpha_token_t(start_line, token_list.size()+1, content, type);
                            } else {
                                std::string type = "NESTED COMMENT BLOCK_COMMENT <-enumerated";

                                token = new alpha_token_t(start_line, token_list.size()+1, content, type);
                            }
    
                            token->add_token_to_list();

                            cmnt_start_line.pop();

                            if (cmnt_start_line.empty()){
                                break;
                            }
                        } else {
                            unput(c);
                        }
                    } else if(c=='/') {
                        if ((c=yyinput())=='*') {
                            cmnt_start_line.push(yyget_lineno());
                        } else {
                            unput(c);
                        }
                    }
                }

                if (!cmnt_start_line.empty())
                    std::cout<< "EOF in comment" <<std::endl;
            }

{COMMENT}   {
                alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
                token = new alpha_token_t(yyget_lineno(), token_list.size()+1, "", "COMMENT LINE_COMMENT <-enumerated");
                token->add_token_to_list();
            }


{CONST_INT}[a-zA-Z_] {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "UNKNOWN TOKEN");
    token->add_token_to_list();
}

{CONST_REAL}[a-zA-Z_] {
    alpha_token_t *token = static_cast<alpha_token_t *>(yylval);
    token = new alpha_token_t(yyget_lineno(), token_list.size()+1, std::string(yytext), "UNKNOWN TOKEN");
    token->add_token_to_list();
}

.   {
        std::cerr << "Unknown token " << yytext << " in line " << yyget_lineno() <<std::endl;
    }

%%
