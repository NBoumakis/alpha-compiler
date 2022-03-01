#include <iostream>
#include <string>
#include <list>


struct alpha_token_t {
  unsigned int     numline;
  unsigned int     numToken;
  std::string      content;
  std::string      type;
  std::string      category;
  struct alpha_token_t *alpha_yylex;

};

extern int yylex();
extern int yylineno;
extern char* yytext;
extern FILE* yyin;
extern alpha_token_t* yylval;

void showlist(std :: list<alpha_token_t> a)
{
    for (struct alpha_token_t x : a) {
		std::cout << x.numline<<" :"  ;
        std::cout <<"   #"<<x.numToken  ;
        std::cout <<"   ""<< x.content <<""" ;
        std::cout <<"   "<< x.type ;
        std::cout <<"   "<< x.category ;
        std::cout <<std::endl ;
	}


}


void printList(struct alpha_token_t *node)
{
    while (node != NULL)
    {   
        std::cout << node->numline<<" :"  ;
        std::cout <<"   #"<<node->numToken  ;
        std::cout <<"   '"<< node->content <<"'" ;
        std::cout <<"   "<< node->type ;
        std::cout <<"   "<< node->category ;
        std::cout <<std::endl ;
        node = node->alpha_yylex;
    }
}

int main(int argc, char** argv){
  std:: list <struct alpha_token_t> alpha_list;


    if(argc>1){
        if (!(yyin = fopen(argv[1], "r"))){
            fprintf(stderr, "Cannot read file: %s\n", argv[1]);
            return -1;
        }
    } else{
        yyin = stdin;
    }
    
    yylex();
    
    printList(yylval);
    return 0;
}





/*std::string names[] = {NULL, "db_type", "db_name", "db_table_prefix", "db_port"};

int main() {
    int ntoken, vtoken;
    ntoken = yylex();
    while (ntoken) {
        std::cout << ntoken << yytext; 
        ntoken = yylex();
    }
    return 0;
}*/
