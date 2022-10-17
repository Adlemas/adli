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
        COMMENT,
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

// Char string for each token type
static const char *TOKEN_TYPE_STRINGS[] = {
    "PLUS",
    "MINUS",
    "MULTIPLY",
    "DIVIDE",
    "MODULO",
    "SEMICOLON",
    "COMMENT",
    "PAREN_OPEN",
    "PAREN_CLOSE",
    "INT",
    "WHITESPACE",
    "_EOF",
};

class Tokenizer
{
    std::string m_source;
    unsigned int pos;

    // tokens
    std::vector<Token *> *m_tokens;

    int m_index = 0;

    void init();

    // Using bool to determine if we should continue

    // Comment
    bool comment();

    // Digit
    bool digit();

    // Token
    bool token();

    // EOF
    bool eof();

public:
    Tokenizer(const std::string &source);
    Tokenizer(const char *source);
    ~Tokenizer();

    void tokenize();
    void reset();
    Token *next_token();
};

#endif