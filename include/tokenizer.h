#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

struct _Token
{
    enum Type
    {
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        MODULO,
        SEMICOLON,
        PAREN_OPEN,
        PAREN_CLOSE,
        INT,
        WHITESPACE,
        _EOF,
    };

    _Token(Type type, const std::string &value) : type(type), value(value) {}

    Type type;
    std::string value;
};
typedef struct _Token Token;

class Tokenizer
{
    std::string m_source;

    // tokens
    std::vector<Token *> *m_tokens;

    int m_index = 0;

    void init();

public:
    Tokenizer(const std::string &source);
    Tokenizer(const char *source);
    ~Tokenizer();

    void tokenize();
    Token *next_token();
};

#endif