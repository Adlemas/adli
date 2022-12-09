#include <astparser.h>

#include <cctype>
#include <algorithm>

using namespace ast;

// Eat token
// If current token is equal to expected token
// then get next token from tokenizer
// else call error function
void Parser::eat(Token::Type type) {
    if (m_current_token->type == type) {
        m_current_token = m_tokenizer->next_token();
    } else {
        if (m_current_token->type == Token::EOF_) {
            std::string token_name = std::string(TOKEN_TYPE_STRINGS[type]);
            std::transform(token_name.begin(), token_name.end(), token_name.begin(), [](unsigned char c) { return std::tolower(c); });
            std::string msg = std::string("Missing " + token_name);
            error(msg.c_str());
        } else {
            error(std::string("Expected token type " + std::string(TOKEN_TYPE_STRINGS[type]) + " but got " +
                              std::string(TOKEN_TYPE_STRINGS[m_current_token->type])).c_str());
        }
    }
}
