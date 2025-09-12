#ifndef LEXER_H
#define LEXER_H
#include <stddef.h>


typedef enum token_type{
    NUMBER, 
	PLUS, MINUS, TIMES, DIVIDE, POWER, DOT,
	LPAREN, RPAREN,
	SIN, COS, TAN,
	UNKNOWN, END
}token_type_t;

typedef struct token{
    const char* lexeme;
    enum token_type type;
    union{
        double decimal;
        int integer;
    };
}token_t;

typedef struct lexer{
    struct stream* stream;
    const char* source;
}lexer_t;

#endif // LEXER_H