#include <tokenizer.h>
#include <cctype>
#include <utility>
#include <iostream>

static const Token TOKENS[] = {
    Token(Token::PLUS, "+"),
    Token(Token::MINUS, "-"),
    Token(Token::MULTIPLY, "*"),
    Token(Token::DIVIDE, "/"),
    Token(Token::MODULO, "%"),
    Token(Token::PAREN_OPEN, "("),
    Token(Token::PAREN_CLOSE, ")"),
    Token(Token::SEMICOLON, ";"),
    Token(Token::QUESTION, "?"),
    Token(Token::COLON, ":"),
    Token(Token::NOT, "!"),
    Token(Token::WHITESPACE, " "),
    Token(Token::WHITESPACE, "\t"),
    Token(Token::WHITESPACE, "\r"),
    Token(Token::WHITESPACE, "\n"),
};

Tokenizer::Tokenizer(std::string source) : m_source(std::move(source))
{
    pos = 0;
    m_tokens = new std::vector<Token *>();
}

Tokenizer::Tokenizer(const char *source) : m_source(source)
{
    pos = 0;
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
        return new Token(Token::EOF_, "");
    }

    Token *token = m_tokens->at(m_index);

    m_index++;

    return token;
}

Token *Tokenizer::peek_token()
{
    if (m_index + 1 >= m_tokens->size())
    {
        // end of tokens
        return new Token(Token::EOF_, "");
    }

    Token *token = m_tokens->at(m_index + 1);

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
        // comments
        if (comment())
        {
            continue;
        }

        // token
        if (token())
        {
            continue;
        }

        // digit
        if (digit())
        {
            continue;
        }

        // identifier
        // but for now raise an error
        error("Invalid character: " + std::string(1, m_source[pos]));
    }

    // EOF
    eof();
}

bool Tokenizer::token()
{
    bool found = false;
    char c = m_source[pos];

    // check if the character is a token
    for (const auto & j : TOKENS)
    {
        if (c == j.value[0])
        {
            found = true;
            // do not add whitespace tokens
            if (j.type == Token::WHITESPACE)
            {
                break;
            }
            m_tokens->push_back(new Token(j.type, j.value));
            break;
        }
    }

    return found;
}

bool Tokenizer::eof()
{
    // add EOF token
    m_tokens->push_back(new Token(Token::EOF_, "EOF"));

    return true;
}

bool Tokenizer::digit()
{
    char c = m_source[pos];

    // check if the character is a digit
    if (isdigit(c))
    {
        // get the whole number
        std::string value;
        value += c;

        // check if the next character is a digit too
        for (int j = (int)pos + 1; j < m_source.length(); j++)
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
            for (int j = (int)pos + 2; j < m_source.length(); j++)
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

void Tokenizer::error(const std::string &message) {
    std::cout << "TokenError: " << message << std::endl;
    exit(1);
}
