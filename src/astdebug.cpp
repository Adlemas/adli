
#include <astdebug.h>
#include <cstring>

void parse_tokenizer(Tokenizer &tokenizer) {
    using namespace ast;

    Parser parser(&tokenizer);

    nodes::StatementsNode *result = parser.parse();

    if (DEBUG) {
        std::cout << std::endl
                  << "Parsed successfully!" << std::endl;
        std::cout << "Statements: " << result->size() << std::endl
                  << std::endl;

        print_nodes(result);
    }
}

void print_tokens(Tokenizer &tokenizer) {
    Token *token = tokenizer.next_token();

    while (token->type != Token::_EOF) {
        std::cout << "Token(" << TOKEN_TYPE_STRINGS[token->type] << "):"
                  << std::string(TOKEN_NAME_MAX_LENGTH - strlen(TOKEN_TYPE_STRINGS[token->type]), ' ') << "\t" << '"'
                  << token->value << '"' << std::endl;
        token = tokenizer.next_token();
    }
}

void print_nodes(ast::nodes::StatementsNode *node) {
    using namespace ast::nodes;
    Node *n = node->current();

    while (n != nullptr) {
        print_node(n, 0);

        node->next();
        n = node->current();
    }
}

void print_node(ast::nodes::Node *node, int tabulation) {
    using namespace ast::nodes;

    if (node == nullptr) {
        return;
    }

    if (node->type() == NodeType::BINARY) {
        auto *binary = (BinaryNode *) node;

        std::cout << std::string(tabulation, ' ') << "BinaryNode: " << OPERATOR_STRINGS[binary->op()] << std::endl;

        print_node(binary->left(), tabulation + TABULATION_SIZE);
        print_node(binary->right(), tabulation + TABULATION_SIZE);
    } else if (node->type() == NodeType::LITERAL) {
        auto *literal = (LiteralNode *) node;

        std::cout << std::string(tabulation, ' ') << "LiteralNode: " << LITERAL_TYPE_STRINGS[literal->literal_type()]
                  << std::endl;

        if (literal->literal_type() == LiteralType::INT) {
            std::cout << std::string(tabulation + TABULATION_SIZE, ' ') << "Value: " << *(int *) literal->value()
                      << std::endl;
        }

        if (literal->literal_type() == LiteralType::FLOAT) {
            std::cout << std::string(tabulation + TABULATION_SIZE, ' ') << "Value: " << *(float *) literal->value()
                      << std::endl;
        }

        if (literal->literal_type() == LiteralType::STRING) {
            std::cout << std::string(tabulation + TABULATION_SIZE, ' ') << "Value: " << (char *) literal->value()
                      << std::endl;
        }

        if (literal->literal_type() == LiteralType::BOOL) {
            std::cout << std::string(tabulation + TABULATION_SIZE, ' ') << "Value: " << (*(bool *) literal->value()
                                                                                         ? "true" : "false")
                      << std::endl;
        }

        if (literal->literal_type() == LiteralType::UNDEFINED) {
            std::cout << std::string(tabulation + TABULATION_SIZE, ' ') << "Value: "
                      << "UNDEFINED" << std::endl;
        }
    } else if (node->type() == NodeType::STATEMENTS) {
        auto *statements = (StatementsNode *) node;

        std::cout << std::string(tabulation, ' ') << "StatementsNode: " << statements->size() << std::endl;

        Node *pNode = statements->current();

        while (pNode != nullptr) {
            print_node(pNode, tabulation + TABULATION_SIZE);

            statements->next();
            pNode = statements->current();
        }
    } else if (node->type() == NodeType::TERNARY) {
        auto *unary = (UnaryNode *) node;

        std::cout << std::string(tabulation, ' ') << "UnaryNode: " << (unary->op() == Operator::MINUS ? '-' : '+')
                  << std::endl;

        print_node(unary->node(), tabulation + TABULATION_SIZE);
    }
}