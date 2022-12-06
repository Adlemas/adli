#include <iostream>
#include <tokenizer.h>
#include <filereader.h>

#include <astdebug.h>

int main()
{
    // std::string source;
    // std::cout << "Enter source: ";
    // std::getline(std::cin, source);

    FileReader file("../test/multiple_expressions.adli");

    std::string source = file.read();

    Tokenizer tokenizer(source);
    tokenizer.tokenize();

    // parse tokens
    parse_tokenizer(tokenizer);

    return 0;
}