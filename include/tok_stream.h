#ifndef TOK_STREAM_H
#define TOK_STREAM_H

#include <stddef.h>

/*
    Token stream is a dymanic array data structure.
    It is the output/return type of the lexer.
*/

// TODO: Add error handling for tok_stream errors.

typedef struct token token_t;

typedef struct stream{
    struct token* buffer;
    size_t length;
    size_t capacity;
}stream_t;


stream_t *create_stream(size_t stream_size);
void stream_destroy(stream_t **stream);

void stream_push_tok(stream_t* stream);
void stream_pop_tok(stream_t* stream);
const token_t *current_token(const stream_t *stream);


#endif // TOK_STREAM_H