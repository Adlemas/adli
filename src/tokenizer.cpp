#include <tokenizer.h>
#include <iostream>
#include <ctype.h>

static const Token TOKENS[] = {
    Token(Token::PLUS, "+"),
    Token(Token::MINUS, "-"),
    Token(Token::MULTIPLY, "*"),
    Token(Token::DIVIDE, "/"),
    Token(Token::MODULO, "%"),
    Token(Token::PAREN_OPEN, "("),
    Token(Token::PAREN_CLOSE, ")"),
    Token(Token::SEMICOLON, ";"),
    Token(Token::WHITESPACE, " "),
    Token(Token::WHITESPACE, "\t"),
    Token(Token::WHITESPACE, "\r"),
    Token(Token::WHITESPACE, "\n"),
};

Tokenizer::Tokenizer(const std::string &source) : m_source(source)
{
    init();
}

Tokenizer::Tokenizer(const char *source) : m_source(source)
{
    init();
}

void Tokenizer::init()
{
    m_tokens = new std::vector<Token *>();
}

Tokenizer::~Tokenizer()
{
    for (Token *token : *m_tokens)
    {
        delete token;
    }

    delete m_tokens;
}

Token *Tokenizer::next_token()
{
    if (m_index >= m_tokens->size())
    {
        // end of tokens
        return new Token(Token::_EOF, "");
    }

    Token *token = m_tokens->at(m_index);

    m_index++;

    return token;
}

/**
 * Tokenize the source code.
 * - This function will tokenize the source code and store the tokens in the
 *  m_tokens vector.
 */
void Tokenizer::tokenize()
{
    for (pos = 0; pos < m_source.length(); pos++)
    {
        char c = m_source[pos];

        // comments
        if (comment())
        {
            continue;
        }

        // token
        // Ignore the return value of token() because we don't care if it
        // returns true or false. We just want to check if it's a token.
        token();

        // digit
        // Ignore the return value of digit() because we don't care if it's a
        // digit or not.
        digit();
    }

    // EOF
    eof();
}

bool Tokenizer::token()
{
    char c = m_source[pos];

    // check if the character is a token
    for (int j = 0; j < sizeof(TOKENS) / sizeof(Token); j++)
    {
        if (c == TOKENS[j].value[0])
        {
            // do not add whitespace tokens apart from the newline token
            if (TOKENS[j].type == Token::WHITESPACE)
            {
                break;
            }
            m_tokens->push_back(new Token(TOKENS[j].type, TOKENS[j].value));
            break;
        }
    }

    return false;
}

bool Tokenizer::eof()
{
    // add EOF token
    m_tokens->push_back(new Token(Token::_EOF, "EOF"));

    return true;
}

bool Tokenizer::digit()
{
    char c = m_source[pos];

    // check if the character is a digit
    if (isdigit(c))
    {
        std::string value = "";
        value += c;

        // check if the next character is a digit
        for (int j = pos + 1; j < m_source.length(); j++)
        {
            if (isdigit(m_source[j]))
            {
                value += m_source[j];
                pos++;
            }
            else
            {
                break;
            }
        }

        m_tokens->push_back(new Token(Token::INT, value));

        return true;
    }

    return false;
}

bool Tokenizer::comment()
{
    char c = m_source[pos];
    // check if comment
    if (c == '/')
    {
        if (m_source[pos + 1] == '/')
        {
            // comment
            std::string comment = "//";

            // get the rest of the comment
            for (int j = pos + 2; j < m_source.length(); j++)
            {
                if (m_source[j] == '\r' || m_source[j] == '\n')
                {
                    break;
                }

                comment += m_source[j];
            }

            m_tokens->push_back(new Token(Token::COMMENT, comment));

            // skip the rest of the comment
            pos += comment.length() - 1;
            return true;
        }
    }

    return false;
}

void Tokenizer::reset()
{
    m_index = 0;
}