#include <astparser.h>

#include <nodes/binary.h>

using namespace ast;

// Term
// factor ((MUL | DIV | MODULO) factor)*
nodes::Node *Parser::term() {
    nodes::Node *result = factor();
    auto *node = new nodes::BinaryNode(result, nullptr);

    while (m_current_token->type == Token::MULTIPLY || m_current_token->type == Token::DIVIDE ||
           m_current_token->type == Token::MODULO) {
        Token *token = m_current_token;

        if (token->type == Token::MULTIPLY) {
            eat(Token::MULTIPLY);
            nodes::Node *right = factor();
            node->setRight(right);
            node->setOp(nodes::Operator::MULTIPLY);

            result = node;
            node = new nodes::BinaryNode(result, nullptr);
        } else if (token->type == Token::DIVIDE) {
            eat(Token::DIVIDE);
            nodes::Node *right = factor();
            node->setRight(right);
            node->setOp(nodes::Operator::DIVIDE);

            result = node;
            node = new nodes::BinaryNode(result, nullptr);
        } else if (token->type == Token::MODULO) {
            eat(Token::MODULO);
            nodes::Node *right = factor();
            node->setRight(right);
            node->setOp(nodes::Operator::MODULO);

            result = node;
            node = new nodes::BinaryNode(result, nullptr);
        } else {
            error(std::string("Unexpected token \"" + token->value + "\"").c_str());
        }
    }

    return result;
}
