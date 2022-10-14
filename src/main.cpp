#include <iostream>
#include <tokenizer.h>

int main()
{
    std::string source;
    std::cout << "Enter source: ";
    std::getline(std::cin, source);

    Tokenizer tokenizer(source);
    tokenizer.tokenize();

    // print tokens
    Token *token = tokenizer.next_token();

    while (token->type != Token::_EOF)
    {
        std::cout << "Token: " << '"' << token->value << '"' << std::endl;
        token = tokenizer.next_token();
    }

    return 0;
}