#include <tokenizer.h>
#include <iostream>

Tokenizer::Tokenizer(const std::string &source)
    : m_source(source)
{
}

Tokenizer::Tokenizer(const char *source)
    : m_source(source)
{
}

Tokenizer::~Tokenizer()
{
    std::cout << "Tokenizer::~Tokenizer()" << std::endl;
}

/**
 * Tokenize the source code.
 * - This function will tokenize the source code and store the tokens in the
 *  m_tokens vector.
 */
void Tokenizer::tokenize()
{
}