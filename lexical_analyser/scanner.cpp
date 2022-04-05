#include "scanner.h"

alpha_token_t::alpha_token_t(int line, int token, std::string content, std::string type)
    : numline(line), numToken(token), content(content), type(type) {}

void alpha_token_t::add_token_to_list() {
    token_list.push_back(this);
}