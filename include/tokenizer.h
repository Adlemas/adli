#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

struct _Token
{
    enum Type
    {
        //
    };

    Type type;
    std::string value;
};
typedef struct _Token Token;

class Tokenizer
{
    std::string m_source;

    // tokens
    std::vector<Token *> *m_tokens;

public:
    Tokenizer(const std::string &source);
    Tokenizer(const char *source);
    ~Tokenizer();

    void tokenize();
};

#endif