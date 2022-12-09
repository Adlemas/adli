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
        eat(Token::INT);

        int *value = new int(std::stoi(token->value));

        return new nodes::LiteralNode(nodes::INT, value);
    } else if (token->type == Token::IDENTIFIER) {
        eat(Token::IDENTIFIER);

        return new nodes::IdentifierNode(token->value);
    } else if (token->type == Token::PAREN_OPEN) {
        eat(Token::PAREN_OPEN);
        nodes::Node *result = expr();
        eat(Token::PAREN_CLOSE);
        return result;
    }
        // Unary operator
        // -factor | !factor
    else if (token->type == Token::MINUS) {
        eat(Token::MINUS);
        nodes::Node *right = factor();
        return new nodes::UnaryNode(right, nodes::Operator::MINUS);
    } else if (token->type == Token::NOT) {
        eat(Token::NOT);
        nodes::Node *right = factor();
        return new nodes::UnaryNode(right, nodes::Operator::NOT);
    }

        // +factor
    else if (token->type == Token::PLUS) {
        eat(Token::PLUS);
        nodes::Node *right = factor();
        return new nodes::UnaryNode(right, nodes::Operator::PLUS);

        // If token is not a factor
        // then call error function
    } else {
        error(std::string("Unexpected token \"" + token->value + "\"").c_str());
        return nullptr;
    }
}
