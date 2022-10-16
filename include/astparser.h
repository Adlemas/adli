#ifndef PARSER_H
#define PARSER_H

#include <tokenizer.h>

class Parser
{
    Tokenizer *m_tokenizer;
    Token *m_current_token;

    void init();

    void error();

    void eat(Token::Type type);

    int factor();

    int term();

    int expr();

    std::vector<int> prog();

public:
    Parser(Tokenizer *tokenizer);
    ~Parser();

    std::vector<int> parse();
};

#endif // PARSER_H