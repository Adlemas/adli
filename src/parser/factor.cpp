#include <astparser.h>

#include <nodes/literal.h>
#include <nodes/identifier.h>
#include <nodes/unary.h>

using namespace ast;

// Factor
// LITERAL | UNARY | PARENTHESIS
nodes::Node *Parser::factor() {
    Token *token = m_current_token;

    if (token->type == Token::INT) {
        // Parse integer literal
        // example: 5

        eat(Token::INT);

        int *value = new int(std::stoi(token->value));

        return new nodes::LiteralNode(nodes::INT, value);
    } else if (token->type == Token::IDENTIFIER) {
        // Parse identifier literal
        // it can be a variable or a function name
        // example: a

        eat(Token::IDENTIFIER);

        return new nodes::IdentifierNode(token->value);
    } else if (token->type == Token::PAREN_OPEN) {
        // Parse parenthesis
        // example: (5 + 5)

        eat(Token::PAREN_OPEN);
        nodes::Node *result = expr();
        eat(Token::PAREN_CLOSE);
        return result;
    } else if (token->type == Token::MINUS) {
        // Unary operator
        // -factor

        eat(Token::MINUS);
        nodes::Node *right = factor();
        return new nodes::UnaryNode(right, nodes::Operator::MINUS);
    } else if (token->type == Token::NOT) {
        // Unary operator
        // !factor
        eat(Token::NOT);
        nodes::Node *right = factor();
        return new nodes::UnaryNode(right, nodes::Operator::NOT);
    } else if (token->type == Token::PLUS) {
        // +factor

        eat(Token::PLUS);
        nodes::Node *right = factor();
        return new nodes::UnaryNode(right, nodes::Operator::PLUS);

    } else {
        // If token is not a factor
        // then call error function

        error(std::string("Unexpected token \"" + token->value + "\"").c_str());
        return nullptr;
    }
}
