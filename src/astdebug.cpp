
#include <astdebug.h>

void print_nodes(ast::nodes::StatementsNode *node)
{
    using namespace ast::nodes;
    Node *n = node->current();

    while (n != nullptr || n != NULL)
    {
        print_node(n, 0);

        node->next();
        n = node->current();
    }
}

void print_node(ast::nodes::Node *node, int tabulation)
{
    using namespace ast::nodes;

    if (node == nullptr || node == NULL)
    {
        return;
    }

    if (node->type() == NodeType::BINARY)
    {
        BinaryNode *binary = (BinaryNode *)node;

        std::cout << std::string(tabulation, ' ') << "BinaryNode: " << OPERATOR_STRINGS[binary->op()] << std::endl;

        print_node(binary->left(), tabulation + TABULATION_SIZE);
        print_node(binary->right(), tabulation + TABULATION_SIZE);
    }
    else if (node->type() == NodeType::LITERAL)
    {
        LiteralNode *literal = (LiteralNode *)node;

        std::cout << std::string(tabulation, ' ') << "LiteralNode: " << LITERAL_TYPE_STRINGS[literal->literal_type()] << std::endl;

        if (literal->literal_type() == LiteralType::INT)
        {
            std::cout << std::string(tabulation + TABULATION_SIZE, ' ') << "Value: " << *(int *)literal->value() << std::endl;
        }

        if (literal->literal_type() == LiteralType::FLOAT)
        {
            std::cout << std::string(tabulation + TABULATION_SIZE, ' ') << "Value: " << *(float *)literal->value() << std::endl;
        }

        if (literal->literal_type() == LiteralType::STRING)
        {
            std::cout << std::string(tabulation + TABULATION_SIZE, ' ') << "Value: " << (char *)literal->value() << std::endl;
        }

        if (literal->literal_type() == LiteralType::BOOL)
        {
            std::cout << std::string(tabulation + TABULATION_SIZE, ' ') << "Value: " << ((*(bool *)literal->value() == true) ? "true" : "false") << std::endl;
        }

        if (literal->literal_type() == LiteralType::UNDEFINED)
        {
            std::cout << std::string(tabulation + TABULATION_SIZE, ' ') << "Value: "
                      << "UNDEFINED" << std::endl;
        }
    }
    else if (node->type() == NodeType::STATEMENTS)
    {
        StatementsNode *statements = (StatementsNode *)node;

        std::cout << std::string(tabulation, ' ') << "StatementsNode: " << statements->size() << std::endl;

        Node *node = statements->current();

        while (node != nullptr || node != NULL)
        {
            print_node(node, tabulation + TABULATION_SIZE);

            statements->next();
            node = statements->current();
        }
    }
    else if (node->type() == NodeType::TERNARY)
    {
        UnaryNode *unary = (UnaryNode *)node;

        std::cout << std::string(tabulation, ' ') << "UnaryNode: " << (unary->op() == Operator::MINUS ? '-' : '+') << std::endl;

        print_node(unary->node(), tabulation + TABULATION_SIZE);
    }
}