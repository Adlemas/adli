
#include <astparser.h>
#include <iostream>

namespace ast
{

    namespace nodes
    {
        Node::Node(NodeType type)
        {
            m_type = type;
        }

        Node::~Node()
        {
        }

        NodeType Node::type()
        {
            return m_type;
        }

        LiteralNode::LiteralNode(LiteralType type, void *value) : Node(LITERAL)
        {
            m_type = type;
            m_value = value;
        }

        LiteralType LiteralNode::literal_type()
        {
            return m_type;
        }

        LiteralNode::~LiteralNode()
        {
        }

        void *LiteralNode::value()
        {
            return m_value;
        }

        BinaryNode::BinaryNode(Node *left, Node *right)
            : Node(BINARY)
        {
            m_left = left;
            m_right = right;
            m_operator = NONE;
        }

        BinaryNode::BinaryNode(Node *left, Node *right, Operator op)
            : Node(BINARY)
        {
            m_left = left;
            m_right = right;
            m_operator = op;
        }

        BinaryNode::~BinaryNode()
        {
            delete m_left;
            delete m_right;
        }

        Node *BinaryNode::left()
        {
            return m_left;
        }

        Node *BinaryNode::right()
        {
            return m_right;
        }

        Operator BinaryNode::op()
        {
            return m_operator;
        }

        void BinaryNode::setLeft(Node *left)
        {
            m_left = left;
        }

        void BinaryNode::setRight(Node *right)
        {
            m_right = right;
        }

        void BinaryNode::setOp(Operator op)
        {
            m_operator = op;
        }

        StatementsNode::StatementsNode()
            : Node(STATEMENTS)
        {
            m_statements = new std::vector<Node *>();
        }

        StatementsNode::~StatementsNode()
        {
            for (auto it = m_statements->begin(); it != m_statements->end(); it++)
            {
                delete *it;
            }
        }

        void StatementsNode::addStatement(Node *statement)
        {
            m_statements->push_back(statement);
        }

        std::vector<Node *> *StatementsNode::statements()
        {
            return m_statements;
        }

        void StatementsNode::next()
        {
            m_index++;
        }

        void StatementsNode::reset()
        {
            m_index = 0;
            next();
        }

        Node *StatementsNode::current()
        {
            if (m_index >= m_statements->size())
            {
                return NULL;
            }

            return m_statements->at(m_index);
        }

        unsigned long int StatementsNode::size()
        {
            return m_statements->size();
        }
    } // namespace nodes

    // Parser class implementation
    void Parser::init()
    {
        m_current_token = m_tokenizer->next_token();
    }

    void Parser::error(const char *msg)
    {
        std::cout << "ParseError: " << msg << std::endl;
    }

    void Parser::eat(Token::Type type)
    {
        if (m_current_token->type == type)
        {
            m_current_token = m_tokenizer->next_token();
        }
        else
        {
            error(std::string("Expected token type " + std::to_string(type) + " but got " + std::to_string(m_current_token->type)).c_str());
        }
    }

    nodes::Node *Parser::factor()
    {
        Token *token = m_current_token;

        if (token->type == Token::INT)
        {
            eat(Token::INT);

            int *value = new int(std::stoi(token->value));

            return new nodes::LiteralNode(nodes::INT, value);
        }
        else if (token->type == Token::PAREN_OPEN)
        {
            eat(Token::PAREN_OPEN);
            nodes::Node *result = expr();
            eat(Token::PAREN_CLOSE);
            return result;
        }
        else
        {
            error(std::string("Unexpected token \"" + token->value + "\"").c_str());
            return NULL;
        }

        return 0;
    }

    nodes::Node *Parser::term()
    {
        nodes::Node *result = factor();
        nodes::BinaryNode *node = new nodes::BinaryNode(result, 0);

        while (m_current_token->type == Token::MULTIPLY || m_current_token->type == Token::DIVIDE || m_current_token->type == Token::MODULO)
        {
            Token *token = m_current_token;

            if (token->type == Token::MULTIPLY)
            {
                eat(Token::MULTIPLY);
                nodes::Node *right = factor();
                node->setRight(right);
                node->setOp(nodes::Operator::MULTIPLY);

                result = node;
                node = new nodes::BinaryNode(result, 0);
            }
            else if (token->type == Token::DIVIDE)
            {
                eat(Token::DIVIDE);
                nodes::Node *right = factor();
                node->setRight(right);
                node->setOp(nodes::Operator::DIVIDE);

                result = node;
                node = new nodes::BinaryNode(result, 0);
            }
            else if (token->type == Token::MODULO)
            {
                eat(Token::MODULO);
                nodes::Node *right = factor();
                node->setRight(right);
                node->setOp(nodes::Operator::MODULO);

                result = node;
                node = new nodes::BinaryNode(result, 0);
            }
            else
            {
                error(std::string("Unexpected token \"" + token->value + "\"").c_str());
            }
        }

        return result;
    }

    nodes::Node *Parser::expr()
    {
        nodes::Node *result = term();
        nodes::BinaryNode *node = new nodes::BinaryNode(result, 0);

        while (m_current_token->type == Token::PLUS || m_current_token->type == Token::MINUS)
        {
            Token *token = m_current_token;

            if (token->type == Token::PLUS)
            {
                eat(Token::PLUS);
                nodes::Node *right = term();
                node->setRight(right);
                node->setOp(nodes::Operator::PLUS);

                result = node;
                node = new nodes::BinaryNode(result, 0);
            }
            else if (token->type == Token::MINUS)
            {
                eat(Token::MINUS);
                nodes::Node *right = term();
                node->setRight(right);
                node->setOp(nodes::Operator::MINUS);

                result = node;
                node = new nodes::BinaryNode(result, 0);
            }
            else
            {
                error(std::string("Unexpected token \"" + token->value + "\"").c_str());
            }
        }

        return result;
    }

    Parser::Parser(Tokenizer *tokenizer)
    {
        m_tokenizer = tokenizer;
        init();
    }

    Parser::~Parser()
    {
    }

    nodes::StatementsNode *Parser::prog()
    {
        nodes::StatementsNode *statements = new nodes::StatementsNode();

        while (m_current_token->type != Token::_EOF)
        {
            // Comment
            if (m_current_token->type == Token::COMMENT)
            {
                eat(Token::COMMENT);
                continue;
            }
            statements->addStatement(expr());
            eat(Token::SEMICOLON);
        }

        return statements;
    }

    nodes::StatementsNode *Parser::parse()
    {
        return prog();
    }
}