
#include <astparser.h>

// DEBUG:
#include <iostream>

void Parser::init()
{
    m_current_token = m_tokenizer->next_token();
}

void Parser::error()
{
    throw "Error parsing input";
}

void Parser::eat(Token::Type type)
{
    if (m_current_token->type == type)
    {
        m_current_token = m_tokenizer->next_token();
    }
    else
    {
        error();
    }
}

int Parser::factor()
{
    Token *token = m_current_token;

    if (token->type == Token::INT)
    {
        eat(Token::INT);
        return std::stoi(token->value);
    }
    else if (token->type == Token::PAREN_OPEN)
    {
        eat(Token::PAREN_OPEN);
        int result = expr();
        eat(Token::PAREN_CLOSE);
        return result;
    }

    return 0;
}

int Parser::term()
{
    int result = factor();

    while (m_current_token->type == Token::MULTIPLY || m_current_token->type == Token::DIVIDE || m_current_token->type == Token::MODULO)
    {
        Token *token = m_current_token;

        if (token->type == Token::MULTIPLY)
        {
            eat(Token::MULTIPLY);
            result *= factor();
        }
        else if (token->type == Token::DIVIDE)
        {
            eat(Token::DIVIDE);
            result /= factor();
        }
        else if (token->type == Token::MODULO)
        {
            eat(Token::MODULO);
            result %= factor();
        }
    }

    return result;
}

int Parser::expr()
{
    int result = term();

    while (m_current_token->type == Token::PLUS || m_current_token->type == Token::MINUS)
    {
        Token *token = m_current_token;

        if (token->type == Token::PLUS)
        {
            eat(Token::PLUS);
            result += term();
        }
        else if (token->type == Token::MINUS)
        {
            eat(Token::MINUS);
            result -= term();
        }
    }

    return result;
}

Parser::Parser(Tokenizer *tokenizer)
{
    m_tokenizer = tokenizer;
    init();
}

Parser::~Parser()
{
}

std::vector<int> Parser::prog()
{
    std::vector<int> results;

    while (m_current_token->type != Token::_EOF)
    {
        results.push_back(expr());
        eat(Token::WHITESPACE);
    }

    return results;
}

std::vector<int> Parser::parse()
{
    return prog();
}