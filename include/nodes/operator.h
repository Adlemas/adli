#ifndef PARSER_OPERATOR_H
#define PARSER_OPERATOR_H

namespace ast {

    namespace nodes {
        enum Operator {
            NONE,
            PLUS,
            MINUS,
            MULTIPLY,
            DIVIDE,
            MODULO,
            NOT,
        };

        // Char string for each operator
        static const char *OPERATOR_STRINGS[] = {
                "NONE",
                "PLUS",
                "MINUS",
                "MULTIPLY",
                "DIVIDE",
                "MODULO",
                "NOT",
        };
    }
}

#endif