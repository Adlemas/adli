#include <astparser.h>

#include <nodes/binary.h>
#include <nodes/ternary.h>

using namespace ast;

// Expression
// term ((PLUS | MINUS) term)*
nodes::Node *Parser::expr() {
    nodes::Node *result = term();
    auto *node = new nodes::BinaryNode(result, nullptr);

    while (m_current_token->type == Token::PLUS || m_current_token->type == Token::MINUS ||
           m_current_token->type == Token::QUESTION) {
        Token *token = m_current_token;

        if (token->type == Token::PLUS) {
            // Parse addition

            eat(Token::PLUS);
            nodes::Node *right = term();
            node->setRight(right);
            node->setOp(nodes::Operator::PLUS);

            result = node;
            node = new nodes::BinaryNode(result, nullptr);
        } else if (token->type == Token::MINUS) {
            // Parse subtraction

            eat(Token::MINUS);
            nodes::Node *right = term();
            node->setRight(right);
            node->setOp(nodes::Operator::MINUS);

            result = node;
            node = new nodes::BinaryNode(result, nullptr);
        }
        else if (token->type == Token::QUESTION) {
            // QUESTION - ternary operator

            eat(Token::QUESTION);
            nodes::Node *left = expr();
            eat(Token::COLON);
            nodes::Node *right = expr();

            result = new nodes::TernaryNode(result, left, right);
        } else {
            error(std::string("Unexpected token \"" + token->value + "\"").c_str());
        }
    }

    return result;
}
