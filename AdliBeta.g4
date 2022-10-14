grammar AdliBeta;

prog: (expr NEWLINE)*;
expr: expr OP expr | INT | PAREN_OPEN+ expr+ PAREN_CLOSE;

PLUS: '+';
MINUS: '-';
MULTIPLY: '*';
DIVIDE: '/';
OP: PLUS | MINUS | MULTIPLY | DIVIDE;
PAREN_OPEN: '(';
PAREN_CLOSE: ')';
NEWLINE: [\r\n]+;
INT: [0-9]+;