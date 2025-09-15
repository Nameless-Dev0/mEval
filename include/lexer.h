#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

typedef struct stream stream_t;
typedef struct token token_t;

typedef struct lexer{
    stream_t* stream;
    const char* source; // must be null-terminated string
    size_t start;
    size_t current;
}lexer_t;

void lexer_init(lexer_t* lexer, const char* line, size_t line_length);
void lex_expression(lexer_t* lexer);
void lexer_reset(lexer_t* lexer);

#endif // LEXER_H

