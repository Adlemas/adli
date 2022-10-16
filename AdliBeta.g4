grammar AdliBeta;

prog: (expr NEWLINE)*;
expr: expr OP expr | INT | PAREN_OPEN+ expr+ PAREN_CLOSE;

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