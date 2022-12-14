#include <tokenizer.h>
#include <filereader.h>

#define DEBUG 1 // set to 0 if PROD mode

#if DEBUG == 1
#include <astdebug.h>
#endif

int main()
{
    // std::string source;
    // std::cout << "Enter source: ";
    // std::getline(std::cin, source);

    FileReader file("../test/main.adli");

    std::string source = file.read();

    Tokenizer tokenizer(source);
    tokenizer.tokenize();

    // parse tokens
    #if DEBUG == 1
    parse_tokenizer(tokenizer);
    #endif

    return 0;
}