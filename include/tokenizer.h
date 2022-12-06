#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <utility>
#include <vector>

struct Token
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
        QUESTION,
        COLON,
        NOT,
        // End of file
        EOF_,
    };

    Token(Type type, std::string value) : type(type), value(std::move(value)) {}

    Type type;
    std::string value;
};

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
    "QUESTION",
    "COLON",
    "NOT",
    "EOF_",
};

class Tokenizer
{
    std::string m_source;
    unsigned int pos;

    // tokens
    std::vector<Token *> *m_tokens;

    int m_index = 0;

    // error
    static void error(const std::string &message);

    // Comment
    bool comment();

    // Digit
    bool digit();

    // Token
    bool token();

    // EOF
    bool eof();

public:
    explicit Tokenizer(std::string source);
    explicit Tokenizer(const char *source);
    ~Tokenizer();

    void tokenize();
    void reset();
    Token *next_token();
    Token *peek_token();
};

#endif