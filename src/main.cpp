#include <iostream>
#include <tokenizer.h>

int main()
{
    std::string source;
    std::cout << "Enter source: ";
    std::getline(std::cin, source);

    Tokenizer tokenizer(source);
    tokenizer.tokenize();

    return 0;
}