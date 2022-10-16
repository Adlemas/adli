grammar AdliBeta;

// Primitive tokens
PLUS: '+';
MINUS: '-';
MULTIPLY: '*';
DIVIDE: '/';
MODULO: '%';
OP: PLUS | MINUS | MULTIPLY | DIVIDE | MODULO;
PAREN_OPEN: '(';
PAREN_CLOSE: ')';
NEWLINE: [\r\n]+;
INT: [0-9]+;
SEMICOLON: ';';

// Keywords
IF: 'if';
ELSE: 'else';

// Identifier
ID: [a-zA-Z_][a-zA-Z0-9_]*;

// Comments
COMMENT: '//' ~[\r

]* -> skip;

prog: (expr SEMICOLON)*;
expr: expr OP expr | INT | PAREN_OPEN+ expr+ PAREN_CLOSE;

// Statements

