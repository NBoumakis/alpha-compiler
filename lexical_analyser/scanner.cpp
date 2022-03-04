#include "scanner.h"

alpha_token_t::alpha_token_t(int line, int token, std::string content, std::string type)
    : numline(line), numToken(token), content(content), type(type) {}