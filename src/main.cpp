#include <iostream>
#include <tokenizer.h>
#include <astparser.h>
#include <filereader.h>

#include <astdebug.h>

void parse_tokenizer(Tokenizer &tokenizer)
{
    using namespace ast;

    Parser parser(&tokenizer);

    nodes::StatementsNode *result = parser.parse();

    print_nodes(result);
}

void parse_statements_node(ast::nodes::StatementsNode *statements)
{
}

void print_tokens(Tokenizer &tokenizer)
{
    Token *token = tokenizer.next_token();

    while (token->type != Token::_EOF)
    {
        std::cout << "Token: " << token->value << std::endl;
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

    // print tokens
    print_tokens(tokenizer);

    tokenizer.reset();

    // parse tokens
    parse_tokenizer(tokenizer);

    return 0;
}