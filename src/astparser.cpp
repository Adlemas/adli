
#include <astparser.h>
#include <iostream>

namespace ast {

    namespace nodes {
        Node::Node(NodeType type) {
            m_type = type;
        }

        Node::~Node() = default;

        NodeType Node::type() {
            return m_type;
        }

        LiteralNode::LiteralNode(LiteralType type, void *value) : Node(LITERAL) {
            m_type = type;
            m_value = value;
        }

        LiteralType LiteralNode::literal_type() {
            return m_type;
        }

        LiteralNode::~LiteralNode() = default;

        void *LiteralNode::value() {
            return m_value;
        }

        BinaryNode::BinaryNode(Node *left, Node *right)
                : Node(BINARY) {
            m_left = left;
            m_right = right;
            m_operator = NONE;
        }

        BinaryNode::BinaryNode(Node *left, Node *right, Operator op)
                : Node(BINARY) {
            m_left = left;
            m_right = right;
            m_operator = op;
        }

        BinaryNode::~BinaryNode() {
            delete m_left;
            delete m_right;
        }

        Node *BinaryNode::left() {
            return m_left;
        }

        Node *BinaryNode::right() {
            return m_right;
        }

        Operator BinaryNode::op() {
            return m_operator;
        }

        void BinaryNode::setLeft(Node *left) {
            m_left = left;
        }

        void BinaryNode::setRight(Node *right) {
            m_right = right;
        }

        void BinaryNode::setOp(Operator op) {
            m_operator = op;
        }

        StatementsNode::StatementsNode()
                : Node(STATEMENTS) {
            m_statements = new std::vector<Node *>();
        }

        StatementsNode::~StatementsNode() {
            for (auto &m_statement: *m_statements) {
                delete m_statement;
            }
        }

        void StatementsNode::addStatement(Node *statement) {
            m_statements->push_back(statement);
        }

        std::vector<Node *> *StatementsNode::statements() {
            return m_statements;
        }

        void StatementsNode::next() {
            m_index++;
        }

        void StatementsNode::reset() {
            m_index = 0;
            next();
        }

        Node *StatementsNode::current() {
            if (m_index >= m_statements->size()) {
                return nullptr;
            }

            return m_statements->at(m_index);
        }

        unsigned long int StatementsNode::size() {
            return m_statements->size();
        }

        TernaryNode::TernaryNode(Node *left, Node *middle, Node *right)
                : Node(TERNARY) {
            m_left = left;
            m_middle = middle;
            m_right = right;
        }

        TernaryNode::~TernaryNode() {
            delete m_left;
            delete m_middle;
            delete m_right;
        }

        Node *TernaryNode::left() {
            return m_left;
        }

        Node *TernaryNode::middle() {
            return m_middle;
        }

        Node *TernaryNode::right() {
            return m_right;
        }

        void TernaryNode::setLeft(Node *left) {
            m_left = left;
        }

        void TernaryNode::setMiddle(Node *middle) {
            m_middle = middle;
        }

        void TernaryNode::setRight(Node *right) {
            m_right = right;
        }

        UnaryNode::UnaryNode(Node *node)
                : Node(UNARY) {
            m_node = node;
            m_operator = NONE;
        }

        UnaryNode::UnaryNode(Node *node, Operator op)
                : Node(UNARY) {
            m_node = node;
            m_operator = op;
        }

        UnaryNode::~UnaryNode() {
            delete m_node;
        }

        Node *UnaryNode::node() {
            return m_node;
        }

        Operator UnaryNode::op() {
            return m_operator;
        }

        void UnaryNode::setNode(Node *node) {
            m_node = node;
        }

        void UnaryNode::setOp(Operator op) {
            m_operator = op;
        }
    } // namespace nodes

    // Parser class implementation
    void Parser::init() {
        m_current_token = m_tokenizer->next_token();
    }

    void Parser::error(const char *msg) {
        std::cout << "ParseError: " << msg << std::endl;
        exit(-1);
    }

    void Parser::eat(Token::Type type) {
        if (m_current_token->type == type) {
            m_current_token = m_tokenizer->next_token();
        } else {
            error(std::string("Expected token type " + std::string(TOKEN_TYPE_STRINGS[type]) + " but got " +
                              std::string(TOKEN_TYPE_STRINGS[m_current_token->type])).c_str());
        }
    }

    Token::Type Parser::peek() {
        return m_tokenizer->peek_token()->type;
    }

    nodes::Node *Parser::factor() {
        Token *token = m_current_token;

        if (token->type == Token::INT) {
            eat(Token::INT);

            int *value = new int(std::stoi(token->value));

            return new nodes::LiteralNode(nodes::INT, value);
        } else if (token->type == Token::PAREN_OPEN) {
            eat(Token::PAREN_OPEN);
            nodes::Node *result = expr();
            eat(Token::PAREN_CLOSE);
            return result;
        }
            // Unary operator
            // -factor
        else if (token->type == Token::MINUS) {
            eat(Token::MINUS);
            nodes::Node *right = factor();
            return new nodes::UnaryNode(right, nodes::Operator::MINUS);
        }
            // +factor
        else if (token->type == Token::PLUS) {
            eat(Token::PLUS);
            nodes::Node *right = factor();
            return new nodes::UnaryNode(right, nodes::Operator::PLUS);
        } else {
            error(std::string("Unexpected token \"" + token->value + "\"").c_str());
            return nullptr;
        }
    }

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

    nodes::Node *Parser::expr() {
        nodes::Node *result = term();
        auto *node = new nodes::BinaryNode(result, nullptr);

        while (m_current_token->type == Token::PLUS || m_current_token->type == Token::MINUS ||
               m_current_token->type == Token::QUESTION) {
            Token *token = m_current_token;

            if (token->type == Token::PLUS) {
                eat(Token::PLUS);
                nodes::Node *right = term();
                node->setRight(right);
                node->setOp(nodes::Operator::PLUS);

                result = node;
                node = new nodes::BinaryNode(result, nullptr);
            } else if (token->type == Token::MINUS) {
                eat(Token::MINUS);
                nodes::Node *right = term();
                node->setRight(right);
                node->setOp(nodes::Operator::MINUS);

                result = node;
                node = new nodes::BinaryNode(result, nullptr);
            }
                // QUESTION - ternary operator
            else if (token->type == Token::QUESTION) {
                eat(Token::QUESTION);
                nodes::Node *middle = expr();
                eat(Token::COLON);
                nodes::Node *right = expr();

                result = new nodes::TernaryNode(result, middle, right);
            } else {
                error(std::string("Unexpected token \"" + token->value + "\"").c_str());
            }
        }

        return result;
    }

    Parser::Parser(Tokenizer *tokenizer) {
        m_tokenizer = tokenizer;
        m_current_token = nullptr;
        init();
    }

    Parser::~Parser() = default;

    nodes::StatementsNode *Parser::prog() {
        auto *statements = new nodes::StatementsNode();

        while (m_current_token->type != Token::EOF_) {
            // Comment
            if (m_current_token->type == Token::COMMENT) {
                eat(Token::COMMENT);
                continue;
            }
            statements->addStatement(expr());
            eat(Token::SEMICOLON);
        }

        return statements;
    }

    nodes::StatementsNode *Parser::parse() {
        return prog();
    }
}