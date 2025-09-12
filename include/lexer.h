#ifndef LEXER_H
#define LEXER_H
#include <stddef.h>

typedef enum token_type token_type_t;
typedef struct token token_t;
typedef struct stream stream_t;
typedef struct lexer lexer_t;

enum token_type{
    NUMBER, 
	PLUS, MINUS, TIMES, DIVIDE, POWER, DOT,
	LPAREN, RPAREN,
	SIN, COS, TAN,
	UNKNOWN, END
};

struct token{
    const char* lexeme;
    token_type_t type;
    union{
        double decimal;
        int integer;
    };
};

struct stream{
    token_t* buffer;
    size_t length;
    size_t capacity;
};

struct lexer{
    stream_t stream;
    const char* source;
};

#endif // LEXER_H