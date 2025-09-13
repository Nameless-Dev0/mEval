#ifndef TOKEN_H
#define TOKEN_H

#define MAX_LEXEME_LENGTH 128

typedef enum token_type{
    NUMBER, 
	PLUS, MINUS, TIMES, DIVIDE, POWER, DOT,
	LPAREN, RPAREN,
	SIN, COS, TAN,
	UNKNOWN, END
}token_type_t;

typedef struct token{
    char lexeme[MAX_LEXEME_LENGTH];
    token_type_t type;
    double value;
}token_t;

token_t* create_token(token_type_t type, const char* lexeme, ...);
void free_token(token_t** token); // not used, going to keep it for now.

#endif // TOKEN_H