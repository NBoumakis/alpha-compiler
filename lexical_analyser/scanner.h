#ifndef __SCANNER_H
#define __SCANNER_H
#include <list>
#include <string>
struct alpha_token_t;

extern std::list<alpha_token_t *> token_list;

struct alpha_token_t {
    unsigned int numline;
    unsigned int numToken;
    std::string content;
    std::string type;

    alpha_token_t(int line, int token, std::string content, std::string type);
    alpha_token_t() {}

    void add_token_to_list() {
        token_list.push_back(this);
    }
};

#endif