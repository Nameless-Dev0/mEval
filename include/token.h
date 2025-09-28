#ifndef TOKEN_H
#define TOKEN_H

#include "lex_limits.h"

typedef enum token_type{
    NUMBER, 
	PLUS, MINUS, MULTIPLY, DIVIDE, POWER,
	LPAREN, RPAREN,
	SIN, COS, TAN,
	UNKNOWN, END
}token_type_t;

typedef struct token{
    char lexeme[MAX_LEXEME_LENGTH]; // always null-terminated
    token_type_t type;
    double value;
}token_t;

token_t* create_token(token_type_t type, const char* lexeme, ...);
void free_token(token_t* token);
void print_token(const token_t* token);

#endif // TOKEN_H