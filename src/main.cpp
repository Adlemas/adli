#include <iostream>
#include <tokenizer.h>
#include <astparser.h>
#include <filereader.h>

#include <astdebug.h>

#define TOKEN_NAME_MAX_LENGTH 20

void parse_tokenizer(Tokenizer &tokenizer)
{
    using namespace ast;

    Parser parser(&tokenizer);

    nodes::StatementsNode *result = parser.parse();

    std::cout << std::endl
              << "Parsed successfully!" << std::endl;
    std::cout << "Statements: " << result->size() << std::endl
              << std::endl;

    print_nodes(result);
}

void print_tokens(Tokenizer &tokenizer)
{
    Token *token = tokenizer.next_token();

    while (token->type != Token::_EOF)
    {
        std::cout << "Token(" << TOKEN_TYPE_STRINGS[token->type] << "):" << std::string(TOKEN_NAME_MAX_LENGTH - strlen(TOKEN_TYPE_STRINGS[token->type]), ' ') << "\t" << '"' << token->value << '"' << std::endl;
        token = tokenizer.next_token();
    }
}

int main()
{
    // std::string source;
    // std::cout << "Enter source: ";
    // std::getline(std::cin, source);

    FileReader file("../test/multiple_expressions.adli");

    std::string source = file.read();

    std::cout << "Source: " << source << std::endl;

    Tokenizer tokenizer(source);
    tokenizer.tokenize();

    // parse tokens
    parse_tokenizer(tokenizer);

    return 0;
}