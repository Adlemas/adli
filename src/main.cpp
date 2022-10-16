#include <iostream>
#include <tokenizer.h>
#include <astparser.h>
#include <filereader.h>

void parse_tokenizer(Tokenizer &tokenizer)
{
    using namespace ast;

    Parser parser(&tokenizer);

    nodes::StatementsNode *result = parser.parse();

    std::cout << "Result: " << result->statements()->size() << std::endl;
}

void print_node(ast::nodes::Node *node)
{
    using namespace ast::nodes;

    if (node->type() == NodeType::BINARY)
    {
        BinaryNode *binary = (BinaryNode *)node;

        std::cout << "BinaryNode: " << binary->op() << std::endl;

        print_node(binary->left());
        print_node(binary->right());
    }
    else if (node->type() == NodeType::LITERAL)
    {
        LiteralNode *literal = (LiteralNode *)node;

        std::cout << "LiteralNode: " << literal->literal_type() << std::endl;

        if (literal->literal_type() == LiteralType::INT)
        {
            std::cout << "Value: " << *(int *)literal->value() << std::endl;
        }

        if (literal->literal_type() == LiteralType::FLOAT)
        {
            std::cout << "Value: " << *(float *)literal->value() << std::endl;
        }

        if (literal->literal_type() == LiteralType::STRING)
        {
            std::cout << "Value: " << (char *)literal->value() << std::endl;
        }

        if (literal->literal_type() == LiteralType::BOOL)
        {
            std::cout << "Value: " << *(bool *)literal->value() << std::endl;
        }

        if (literal->literal_type() == LiteralType::UNDEFINED)
        {
            std::cout << "Value: "
                      << "UNDEFINED" << std::endl;
        }
    }
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